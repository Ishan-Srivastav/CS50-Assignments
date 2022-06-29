select movies.title , ratings.rating
from movies
join ratings on movies.id=ratings.movie_id
where movies.year=2010
order by rating desc, title asc;
