/* list the names of all people who starred in a movie in which Kevin Bacon also starred */
SELECT DISTINCT name from movies
	JOIN stars ON movies.id = stars.movie_id
	JOIN people ON stars.person_id = people.id
WHERE movies.id in (SELECT movie_id FROM people
	JOIN stars ON people.id = stars.person_id
	JOIN movies ON stars.movie_id = movies.id
	WHERE name = "Kevin Bacon") AND name != "Kevin Bacon"