/* list the titles of all movies in which 
both Johnny Depp and Helena Bonham Carter starred */
SELECT movies.title FROM people
	JOIN stars ON people.id = stars.person_id
	JOIN movies ON stars.movie_id = movies.id
WHERE people.name in ('Johnny Depp', 'Helena Bonham Carter')
GROUP BY title
HAVING count(movies.title) = 2