---
title: sqlalchemy - the python sql toolkit and object relational mapper
published: true
---

## FAQ: 

* What is the difference between .one() and .scalar() in SQLAlchemy ?

```
one() 
  Return exactly one result or raise an exception 
  Raises sqlalchemy.orm.exc.NoResultFound if the query selects no rows. 
  Raises sqlalchemy.orm.exc.MultipleResultsFound if multiple object identities are returned. 

scalar()
  Return the first element of the first result or None if no rows present. If multiple rows are returned, raises MultipleResultsFound.

ISO 8601 string:
  import datetime 
  datetime.datetime.now().isoformat() 
  »> '2020-08-17T21:04:47.773937' 

```
