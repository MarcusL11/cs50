--- Keep a log of any SQL queries you execute as you solve the mystery.

-- Filter a list of crimes related to duck theft
SELECT * FROM crime_scene_reports
WHERE description LIKE '%thef%'
   AND description LIKE '%CS50%'
   AND description LIKE '%duck%';
-- Info on Crime Scene
-- | id  | year | month | day |     street      |                                                                                                       descriptio                                                                                                         |
-- | 295 | 2024 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- Key Information: Three witnesses, Interview on July 28 2024, interview transcripts mentions the bakery.

-- Reading the transacript from the witnesses on that day
SELECT name, transcript FROM interviews
WHERE year = 2024
AND month = 7
AND day = 28
AND transcript
LIKE "%bakery%";

-- Key information:
-- -- Ruth: ten minutes of the theft, security footage from the bakery parking lot look for car around the time
-- -- Eugene: ATM on Leggett Street and saw the thief there withdrawing some money.

-- Connection:
-- -- Security Footage: 10:15am (left parking appox. 10:25) , Location: Humphrey Street bakery
-- -- ATM: Leggett Street, July 28th before 10am, withdrawal
-- -- Phone Calls: Suspect made outgoing call for less than a minute approx 10:25am July 28
-- -- Flights: "earliest flight out of Fiftyville tomorrow (July 29th Morning).
-- -- Tickets: Helper to purchase the flight ticket.

-- List atm transactions that occured July 28th 2024 with transaction type withdrawal
-- -- ATM: Leggett Street, July 28th before 10am, withdrawal
SELECT account_number
FROM atm_transactions
WHERE year = 2024 AND
month = 7 AND
day = 28 AND
atm_location LIKE "%Leggett%";

-- +----------------+
-- | account_number |
-- +----------------+
-- | 28500762       |
-- | 28296815       |
-- | 76054385       |
-- | 49610011       |
-- | 16153065       |
-- | 86363979       |
-- | 25506511       |
-- | 81061156       |
-- | 26013199       |
-- +----------------+

-- Link account numbers to People
SELECT * FROM people
WHERE id = (
   SELECT person_id
   FROM bank_accounts
   WHERE account_number IN (
      SELECT account_number
      FROM atm_transactions
      WHERE year = 2024 AND
      month = 7 AND
      day = 28 AND
      atm_location LIKE "%Leggett%"
   )
);
-- SUSPECTED THEIF from using ATM and
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+



-- Find the license_plates from the approx time of the theft event
-- -- Security Footage: 10:15am (left parking appox. 10:25) , Location: Humphrey Street bakery
SELECT activity, license_plate, hour, minute
FROM bakery_security_logs
WHERE year = 2024 AND
month = 7 AND
day = 28 AND
hour = 10 AND
license_plate IN (
SELECT license_plate FROM people
   WHERE id = (
      SELECT person_id
      FROM bank_accounts
      WHERE account_number IN (
         SELECT account_number
         FROM atm_transactions
         WHERE year = 2024 AND
         month = 7 AND
         day = 28 AND
         atm_location LIKE "%Leggett%"
      )
   )
);
-- +----------+---------------+------+--------+
-- | activity | license_plate | hour | minute |
-- +----------+---------------+------+--------+
-- | exit     | 94KL13X       | 10   | 18     |
-- +----------+---------------+------+--------+

-- Check the people that made phone calls that day
-- -- Phone Calls: Suspect made outgoing call for less than a minute approx 10:25am July 28 that mathces Suspect form ATM
SELECT caller, receiver, duration FROM phone_calls
WHERE year = 2024 AND
month = 7 AND
day = 28 AND
duration <=60 AND caller IN (
   SELECT phone_number FROM people
   WHERE id = (
      SELECT person_id
      FROM bank_accounts
      WHERE account_number IN (
         SELECT account_number
         FROM atm_transactions
         WHERE year = 2024 AND
         month = 7 AND
         day = 28 AND
         atm_location LIKE "%Leggett%"
      )
   )
);

-- +----------------+----------------+----------+
-- |     caller     |    receiver    | duration |
-- +----------------+----------------+----------+
-- | (367) 555-5533 | (375) 555-8161 | 45       |
-- +----------------+----------------+----------+

-- Check if the suspect from the ATM is on any flights linking bank account number
-- -- Flights: "earliest flight out of Fiftyville tomorrow (July 29th Morning).
SELECT * FROM passengers
WHERE passport_number IN (
   SELECT passport_number FROM people
   WHERE id = (
      SELECT person_id
      FROM bank_accounts
      WHERE account_number IN (
         SELECT account_number
         FROM atm_transactions
         WHERE year = 2024 AND
         month = 7 AND
         day = 28 AND
         atm_location LIKE "%Leggett%"
      )
   )
);

-- +-----------+-----------------+------+
-- | flight_id | passport_number | seat |
-- +-----------+-----------------+------+
-- | 36        | 5773159633      | 4A   |
-- +-----------+-----------------+------+

-- Fetching flights that matches the suspect who used the ATM
SELECT *
FROM flights
JOIN passengers ON passengers.flight_id = flights.id
WHERE passengers.passport_number IN (
    SELECT passport_number
    FROM people
    WHERE id = (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE year = 2024
              AND month = 7
              AND day = 28
              AND atm_location LIKE '%Leggett%'
        )
    )
)
AND flights.id IN (
    SELECT flight_id
    FROM passengers
    WHERE passport_number IN (
        SELECT passport_number
        FROM people
        WHERE id = (
            SELECT person_id
            FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2024
                  AND month = 7
                  AND day = 28
                  AND atm_location LIKE '%Leggett%'
            )
        )
    )
);

-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
-- | 36 | 8                 | 4                      | 2024 | 7     | 29  | 8    | 20     | 36        | 5773159633      | 4A   |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+


SELECT * FROM airports
WHERE id IN (
   SELECT origin_airport_id
   FROM flights
   JOIN passengers ON passengers.flight_id = flights.id
   WHERE passengers.passport_number IN (
      SELECT passport_number
      FROM people
      WHERE id = (
         SELECT person_id
         FROM bank_accounts
         WHERE account_number IN (
               SELECT account_number
               FROM atm_transactions
               WHERE year = 2024
               AND month = 7
               AND day = 28
               AND atm_location LIKE '%Leggett%'
         )
      )
   )
   AND flights.id IN (
      SELECT flight_id
      FROM passengers
      WHERE passport_number IN (
         SELECT passport_number
         FROM people
         WHERE id = (
               SELECT person_id
               FROM bank_accounts
               WHERE account_number IN (
                  SELECT account_number
                  FROM atm_transactions
                  WHERE year = 2024
                     AND month = 7
                     AND day = 28
                     AND atm_location LIKE '%Leggett%'
               )
         )
      )
   )
);
-- +----+--------------+-----------------------------+------------+
-- | id | abbreviation |          full_name          |    city    |
-- +----+--------------+-----------------------------+------------+
-- | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
-- +----+--------------+-----------------------------+------------+

SELECT * FROM airports
WHERE id IN (
   SELECT destination_airport_id
   FROM flights
   JOIN passengers ON passengers.flight_id = flights.id
   WHERE passengers.passport_number IN (
      SELECT passport_number
      FROM people
      WHERE id = (
         SELECT person_id
         FROM bank_accounts
         WHERE account_number IN (
               SELECT account_number
               FROM atm_transactions
               WHERE year = 2024
               AND month = 7
               AND day = 28
               AND atm_location LIKE '%Leggett%'
         )
      )
   )
   AND flights.id IN (
      SELECT flight_id
      FROM passengers
      WHERE passport_number IN (
         SELECT passport_number
         FROM people
         WHERE id = (
               SELECT person_id
               FROM bank_accounts
               WHERE account_number IN (
                  SELECT account_number
                  FROM atm_transactions
                  WHERE year = 2024
                     AND month = 7
                     AND day = 28
                     AND atm_location LIKE '%Leggett%'
               )
         )
      )
   )
);

-- +----+--------------+-------------------+---------------+
-- | id | abbreviation |     full_name     |     city      |
-- +----+--------------+-------------------+---------------+
-- | 4  | LGA          | LaGuardia Airport | New York City |
-- +----+--------------+-------------------+---------------+

-- Getting the reciving caller details from the suspect, assuming is the helper
SELECT * FROM people
WHERE phone_number IN (
   SELECT receiver FROM phone_calls
   WHERE year = 2024 AND
   month = 7 AND
   day = 28 AND
   duration <=60 AND caller IN (
      SELECT phone_number FROM people
      WHERE id = (
         SELECT person_id
         FROM bank_accounts
         WHERE account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE year = 2024 AND
            month = 7 AND
            day = 28 AND
            atm_location LIKE "%Leggett%"
         )
      )
   )
);
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 864400 | Robin | (375) 555-8161 | NULL            | 4V16VO0       |
-- +--------+-------+----------------+-----------------+---------------+
- Keep a log of any SQL queries you execute as you solve the mystery.

