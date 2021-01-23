/* list the names of all people who starred in Toy Story */
SELECT people.name FROM stars
INNER JOIN people ON stars.person_id = people.id
INNER JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = "Toy Story"