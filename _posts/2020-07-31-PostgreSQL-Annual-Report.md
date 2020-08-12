---
title: PostgreSQL Annual Report
published: true
---

* StackOver Flow High frequency problem 

```
1. Postgresql: UUID or SEQUENCE for primary key?
  A sequence in PostgreSQL does exactly the same as AUTOINCREMENT in MySQL. A sequence is more efficient than a uuid because it is 8 bytes instead of 16 for the uuid. You can use a uuid as a primary key, just like most any other data type. 

  It you want to protect a table with user data from snooping hackers that are trying to guess other IDs, the uuid type is an excellent choice. 

  **id uuid PRIMARY KEY DEFAULT uuid_generate_v4()**


```
