import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["POST", "GET"])
@login_required
def index():
    """Show portfolio of stocks"""

    if request.method == "POST":
        # validate user's input:
        cash = request.form.get("cash")

        # convert to int
        try:
            cash = int(cash)
        except ValueError as e:
            return apology(f"{e} meeow!")

        if not cash or cash < 0:
            return apology("Numbers only and greater than 0! Meoww!")

        beginning_balance = db.execute(
            "SELECT cash from users WHERE id = ?", session["user_id"]
        )
        ending_balance = beginning_balance[0]["cash"] + cash

        try:
            # From Users Table
            user_result = db.execute(
                "UPDATE users SET cash = ? WHERE id = ?",
                ending_balance,
                session["user_id"],
            )

        except (ValueError, RuntimeError) as e:
            return apology(f"{e}...meow!")

        return redirect("/")

    if request.method == "GET":
        try:
            # From Portfolio Table
            stocks = db.execute(
                "SELECT symbol, SUM(shares) AS total_shares FROM portfolio WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
                session["user_id"],
            )

            # From Users Table
            user_result = db.execute(
                "SELECT * FROM users WHERE id = ?", session["user_id"]
            )

        except (ValueError, RuntimeError) as e:
            return apology(f"{e}...meow!")

        username = user_result[0]["username"]
        cash = user_result[0]["cash"]
        cash_balance = usd(cash)

        portfolio_value = 0

        for stock in stocks:
            # Get current market price
            quote = lookup(stock["symbol"])
            if quote:
                stock["price"] = quote["price"]
                stock["total_value"] = stock["price"] * stock["total_shares"]
                portfolio_value += stock["total_value"]
                stock["price"] = usd(stock["price"])
                stock["total_value"] = usd(stock["total_value"])
            else:
                stock["price"] = "N/A"
                stock["total_vaue"] = "N/A"

        grand_total = usd(float(portfolio_value + cash))
        portfolio_value = usd(portfolio_value)

        return render_template(
            "index.html",
            stocks=stocks,
            username=username,
            cash_balance=cash_balance,
            grand_total=grand_total,
            portfolio_value=portfolio_value,
        )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":
        # call lookup to look up a stock’s current price.
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or not symbol.isalpha():
            return apology(f"Need a symbol..meow!")

        try:
            shares = int(shares)
        except ValueError as e:
            return apology(f"{e}..meow error!")

        if shares < 0:
            return apology("Please set shares to positive number values only .")

        try:
            stock = lookup(symbol)
        except (KeyError, ValueError) as e:
            return apology(f"{e}...sorry meow!")

        if not stock:
            return apology("Need a valid symbol", 400)

        # Check user's cash balance
        try:
            user = db.execute(
                "SELECT id, cash FROM users WHERE id = ?", session["user_id"]
            )
        except (ValueError, RuntimeError) as e:
            return apology(f"{e}...meow!")

        amount_per_share = stock.get("price")
        total_amount = float(amount_per_share) * shares

        # Check User cash is enough to purchase
        if user[0]["cash"] < total_amount:
            return apology("No money no honey!")

        updated_cash = user[0]["cash"] - total_amount

        try:
            import datetime

            # Create record in transaction and portfolio table
            date_time = datetime.datetime.now()
            type = "buy"
            db.execute(
                "INSERT INTO transactions (user_id, symbol, shares, total_amount, amount_per_share, type, date_time) VALUES (?, ?, ?, ?, ?, ?, ?)",
                session["user_id"],
                symbol,
                shares,
                total_amount,
                amount_per_share,
                type,
                date_time,
            )
            db.execute(
                "INSERT INTO portfolio (user_id, symbol, shares, total_amount, amount_per_share, date_time) VALUES (?, ?, ?, ?, ?, ?)",
                session["user_id"],
                symbol,
                shares,
                total_amount,
                amount_per_share,
                date_time,
            )

            # update record in user table
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?",
                updated_cash,
                session["user_id"],
            )
        except (ValueError, RuntimeError) as e:
            return apology(f"{e}...meow!")

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Fetch transaction data
    try:
        transactions = db.execute(
            "SELECT * FROM transactions WHERE user_id = ? ORDER BY date_time DESC",
            session["user_id"],
        )
    except (ValueError, RuntimeError) as e:
        return apology(f"{e}...meow!")

    for tx in transactions:
        tx["amount_per_share"] = usd(tx["amount_per_share"])
        tx["total_amount"] = f"{float(tx['total_amount']):.2f}"

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol or not symbol.isalpha():
            return apology("Provide a valid symbol MEOW!")

        try:
            result = lookup(symbol)

        except (KeyError, ValueError) as e:
            return apology(f"{e}...sorry meow!")

        if not result:
            return apology("Stock does not exists")

        result["price"] = usd(result["price"])

        return render_template("quoted.html", stock=result)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # validate username
        if not username:
            return apology("Provide username MEOW!")

        # validate user's password
        if not password:
            return apology("Provide password MEOW!")

        if not confirmation:
            return apology("Provide confirm password MEOW!")

        if password != confirmation:
            return apology("Your passwords don't match MEOW!")

        # Hash the password
        hash = generate_password_hash(password, method="scrypt", salt_length=16)

        # Insert username to db
        try:
            # Insert username to db
            db.execute(
                "INSERT INTO users (username, hash ) VALUES (?, ?)", username, hash
            )

        except (ValueError, RuntimeError) as e:
            return apology(f"{e}...MEOW!")

        return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        try:
            current_stocks = db.execute(
                "SELECT symbol FROM portfolio WHERE user_id = ? GROUP BY symbol",
                session["user_id"],
            )
        except (ValueError, RuntimeError) as e:
            return apology(f"{e}...meow!")

        return render_template("sell.html", current_stocks=current_stocks)

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_input = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol")

        if not shares_input:
            return apology("must provide shares")

        try:
            shares = int(shares_input)
        except ValueError as e:
            return apology(f"{e}...meow!")

        if shares <= 0:
            return apology("Shares must be a positive integer")

        try:
            # From Transactions table
            current_stocks = db.execute(
                "SELECT * FROM portfolio WHERE user_id = ? ORDER BY date_time ASC",
                session["user_id"],
            )

            # From Users Table
            user_result = db.execute(
                "SELECT * FROM users WHERE id = ?", session["user_id"]
            )

        except (ValueError, RuntimeError) as e:
            return apology(f"{e}...meow!")

        shares_amount_own = 0
        valid_symbol = False

        # Validating the user's stock symbol
        for stock in current_stocks:
            if symbol == stock["symbol"]:
                print("Found stock in portfolio!")
                valid_symbol = True
                shares_amount_own += stock["shares"]

        if not valid_symbol:
            return apology("Please choose a stock you own..meow!")

        print("Symbol validated")

        # Validating the user's shares amount
        if shares > shares_amount_own:
            return apology(f"Please select an amount <= {shares_amount_own}..meow!")

        print("Shares amount validated")

        # Get the current stock price
        try:
            result = lookup(symbol)

        except (KeyError, ValueError) as e:
            return apology(f"{e}...sorry meow!")

        if not result:
            return apology("Not a valid sale", 400)

        # instantiate shares to track different purchases of same stock
        share_amount_to_sell = shares

        for index, stock in enumerate(current_stocks):
            if share_amount_to_sell == 0:
                print("Breaking from loop")
                break

            print("Loop: ", index)

            if symbol == stock["symbol"]:
                print("Found Stock")

                if share_amount_to_sell > stock["shares"]:
                    print("Amount to sell > than stock shares")
                    # Remove the current stock shares from the portfolio table
                    db.execute(
                        "DELETE FROM portfolio WHERE user_id = ? AND id = ?",
                        session["user_id"],
                        stock["id"],
                    )
                    print("removing stock ID: ", stock["id"])

                    # Update share_amount_to_sell
                    share_amount_to_sell -= stock["shares"]
                    print("removing shares from tracker: ", stock["shares"])
                    print("Remaining share to sell: ", share_amount_to_sell)

                elif share_amount_to_sell < stock["shares"]:
                    print("Amount to sell < than stock shares")
                    # Update the current stock shares from the portfolio table
                    updated_shares = stock["shares"] - share_amount_to_sell

                    db.execute(
                        "UPDATE portfolio SET shares = ? WHERE user_id = ? AND id = ?",
                        updated_shares,
                        session["user_id"],
                        stock["id"],
                    )
                    print("Updating shares in stock ID: ", stock["id"])
                    print("Starting shares: ", stock["shares"])
                    print("Ending shares: ", updated_shares)

                    # Update share_amount_to_sell
                    print("removing shares from tracker: ", share_amount_to_sell)
                    share_amount_to_sell = 0

                elif share_amount_to_sell == stock["shares"]:
                    print("Amount to sell = stock shares")
                    # Remove the current stock shares from the portfolio table
                    db.execute(
                        "DELETE FROM portfolio WHERE user_id = ? AND id = ?",
                        session["user_id"],
                        stock["id"],
                    )
                    print("removing stock ID: ", stock["id"])

                    # Update share_amount_to_sell
                    print("removing shares from tracker: ", share_amount_to_sell)
                    share_amount_to_sell = 0
                    print("Remaining share to sell: ", share_amount_to_sell)

        # Create the sell on the transaction table
        print(f"Creating Sell transaction for {shares} shares")

        # getting the total dollar amount from the sale
        amount_per_share = result["price"]
        print("amount per share: ", amount_per_share)

        type = "sell"

        total_amount = shares * amount_per_share
        print("Shares: ", shares)
        print("Total Amount: ", total_amount)

        import datetime

        date_time = datetime.datetime.now()

        print("Amount per share", amount_per_share)
        print("Transaction type", type)
        print("Total Amount", total_amount)

        # Create record in transaction table
        db.execute(
            "INSERT INTO transactions (user_id,  symbol, shares, total_amount, amount_per_share, type, date_time) VALUES (?, ?, ?, ?, ?, ?, ?)",
            session["user_id"],
            symbol,
            shares,
            total_amount,
            amount_per_share,
            type,
            date_time,
        )

        updated_cash = float(user_result[0]["cash"] + total_amount)

        # update the user's cash balanace
        print("User's beginning cash balance: ", user_result[0]["cash"])
        print("....Sell Amount: ", total_amount)
        print("User's ending cash balance: ", updated_cash)
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ? ", updated_cash, session["user_id"]
        )

        return redirect("/")
