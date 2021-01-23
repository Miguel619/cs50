/* determine the average rating of all movies released in 2012 */
SELECT SUM(ratings.rating)/count(movies.id) FROM ratings 
INNER JOIN movies ON ratings.movie_id = movies.id WHERE movies.year = 2012