> Lorenzo De Bie

# Labo 4: Hashing

## Differences in speeds
All times are in milliseconds.  
Calculated with all the files in the quiz folder.

### Jaccard index
Time of Unique integers and Hashing is the sum of time it took to replace the strings and to execute the Jaccard function.  
Minhashing with 300 hashes.

Strings | Unique integers | Hashes | MinHashing Unique integers | MinHashing Hashes
--- | --- | --- | --- | ---
792 | 609 | 625 | 334 | 341
918 | 664 | 650 | 365 | 351
811 | 651 | 638 | 356 | 357
813 | 662 | 635 | 355 | 347
819 | 662 | 642 | 346 | 350
839 | 648 | 629 | 351 | 351
874 | 674 | 631 | 353 | 347
822 | 659 | 628 | 351 | 348
827 | 717 | 786 | 443 | 350
817 | 658 | 632 | 344 | 365

#### Averages & speed increases

Type | Average | Speed increase
--- | ---| ---
Strings | 833.2 | /
Unique integers | 660.4 | 26.17%
Hashes | 649.6 | 28.26%
MinHashing Unique integers | 359.8 | 131.47%
MinHashing Hashes | 350.7 | 137.58%

### Hashing
I only tested these hashing algorithms because these are the only ones who give less than 5 collisions
 with our data [see Collisions](#collisions)

good_hash | djb2 | sdbm | stl_hash | jenkins_one_at_a_time_hash
--- | --- | --- | --- |---
9 | 9 | 9 | 6 | 7
9 | 9 | 9 | 7 | 8
10 | 10 | 13 | 8 | 11
9 | 9 | 9 | 6 | 7
11 | 11 | 11 | 8 | 9

stl_hash performs best in all of the runs

## Collisions
Calculated with all the files in the quiz folder.

Hash function | Number of collision
--- | ---
worst_hash | 3346
bad_hash | 3338
other_bad_hash | 2005
horner_hash | 3037
good_hash | 0
djb2 | 2
sdbm | 0
lose_lose | 2005
stl_hash | 0
jenkins_one_at_a_time_hash | 0
