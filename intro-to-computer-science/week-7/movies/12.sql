
-- write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Bradley Cooper.
-- You may assume that there is only one person in the database with the name Jennifer Lawrence.

-- Setting the columns to select movie titles
SELECT movies.title FROM movies
-- Where movies contain both actors
WHERE movies.id IN(
    -- Subquery to find movie IDs with both actors, selecting the movie_id from stars table
    SELECT stars.movie_id FROM stars
    -- Filtering for the two actors
    WHERE person_id IN (
        SELECT people.id FROM people WHERE people.name = "Bradley Cooper"
        UNION
        SELECT people.id FROM people WHERE people.name = "Jennifer Lawrence"
    )
    -- Create a group by to count distinct person IDs per movie
    GROUP BY stars.movie_id
    HAVING COUNT(DISTINCT stars.person_id) = 2
)

