/* list the names of all people who starred in a movie released in 2004, ordered by birth year */
SELECT people.name FROM stars
INNER JOIN people ON stars.person_id = people.id
INNER JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth