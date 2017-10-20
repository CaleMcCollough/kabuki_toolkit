/** The Chinese Room
    @version 0.x
    @file    ~/source/kabuki/chinese_room/impl/table.cc
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough.github.io>;
             All right reserved (R). Licensed under the Apache License, Version 
             2.0 (the "License"); you may not use this file except in 
             compliance with the License. You may obtain a copy of the License 
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless 
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License.
*/

#include <stdafx.h>
#include "../include/table.h"
#include "../include/utils.h"
#include "../include/error.h"

namespace _ {

static Table* TableInit (byte* buffer, byte max_keys, uint16_t total_size)
{
    if (buffer == nullptr)
        return nullptr;
    Table* table = reinterpret_cast<Table*>(buffer);

    uint_t min_required_size = sizeof (Table) + max_keys * 
                               (kOverheadPerRecord + 2);
    if (total_size < min_required_size)
        return nullptr;

    table->num_keys = 0;
    table->max_keys = max_keys;
    table->pile_size = 0;
    table->size = total_size;
    return table;
}

static byte TableAdd (Table* table, const char* key) {
    if (table == nullptr) return 0;
    if (key == nullptr) return 0;
    
    //PrintStringLine (key);

    byte num_keys = table->num_keys,
        max_keys  = table->max_keys,
        temp;

    uint16_t size = table->size;

    if (num_keys >= max_keys) return kTableFull;
    //< We're out of buffered indexes.

    hash16_t* hashes = reinterpret_cast<hash16_t*> (reinterpret_cast<byte*> (table) +
        sizeof (Table));
    uint16_t* key_offsets = reinterpret_cast<uint16_t*> (hashes + 
        max_keys);
    byte* indexes = reinterpret_cast<byte*> (key_offsets + 
                    max_keys),
        *unsorted_indexes = indexes + max_keys,
        *collission_list = unsorted_indexes + max_keys;
    char* keys = reinterpret_cast<char*> (table) + size - 1,
        *destination;

    // Calculate space left.
    uint16_t value = size - max_keys * kOverheadPerRecord,
        pile_size,
        key_length = static_cast<uint16_t> (strlen (key));

    //PrintLine ();
    //printf ("Adding Key %s\n%20s: 0x%p\n%20s: %p\n%20s: 0x%p\n"
    //    "%20s: %p\n%20s: %u\n", key, "hashes", hashes, "key_offsets", 
    //    key_offsets, "keys", keys, "indexes", indexes, "value", value);

    hash16_t hash = Hash16 (key),
        current_hash;

    if (key_length > value)
    {
        //printf ("Buffer overflow\n");
        return BufferOverflowError;
    }

    //print ();

    if (num_keys == 0)
    {
        table->num_keys = 1;
        *hashes = hash;
        *key_offsets = static_cast<uint16_t> (key_length);
        *indexes = kNoCollidingRecords;
        *unsorted_indexes = 0;
        destination = keys - key_length;

        CopyString (destination, key);
        //printf ("Inserted key %s at GetAddress 0x%p\n", key, destination);
        //Print (table);
        return 0;
    }

    // Calculate left over buffer size by looking up last string.

    if (key_length >= value)
    {
        //printf ("Not enough room in buffer!\n");
        return 0;   //< There isn't enough room left in the buffer.
    }

    //printf ("Finding insert location... \n");

    int low = 0,
        mid,
        high = num_keys,
        index;

    byte* temp_ptr;

    while (low <= high)
    {
        mid = (low + high) >> 1;        //< Shift >> 1 to / 2

        current_hash = hashes[mid];
        //printf ("high: %i mid: %i low %i hash: %x\n", high, mid, low, 
        //        current_hash);

        if (current_hash > hash)
        {
            high = mid - 1;
        }
        else if (current_hash < hash)
        {
            low = mid + 1;
        }
        else    // Duplicate hash detected.
        {
            //printf ("hash detected, ");

            // Check for other collisions.

            index = indexes[mid];       //< Index in the collision table.

            //printf ("index:%u\n", index);

            if (index < kNoCollidingRecords)   //< There are other collisions.
            {
                //printf ("with collisions, ");
                // There was a collision so check the table.

                // The collisionsList is a sequence of indexes terminated 
                // by an invalid index. collissionsList[0] is 
                // an invalid index, so the collisionsList is searched from
                // lower address up.
                temp = indexes[mid];
                temp_ptr = collission_list + temp;
                index = *temp_ptr;  //< Load the index in the collision table.
                while (index < kMaxNumOperations) {
                    //printf ("comparing to \"%s\"\n", keys - key_offsets[index]);
                    if (strcmp (key, keys - key_offsets[index]) == 0) {
                        //printf ("but table already contains key at "
                         //       "offset: %u.\n", index);
                        return index;
                    }
                    ++temp_ptr;
                    index = *temp_ptr;
                }

                // Its a new collision!
                //printf ("and new collision detected.\n");
                
                // Copy the key
                value = key_offsets[num_keys - 1] + key_length + 1;
                CopyString (keys - value, key);
                key_offsets[num_keys] = value;

                // Update the collision table.
                pile_size = table->pile_size;
                // Shift the collisions table up one element and insert 
                // the unsorted collision index.
                // Then move to the top of the collisions list.
                collission_list += pile_size;
                // and iterate down to the insert spot
                while (collission_list > temp_ptr)
                {
                    *collission_list = *(collission_list - 1);
                    --collission_list;
                }
                *temp_ptr = num_keys;

                table->pile_size = pile_size + 1;
                //printf ("\n\ncollision index: %u\n", temp);
                // Store the collision index.
                indexes[num_keys] = temp;   //< Store the collision index
                table->num_keys = num_keys + 1;
                hashes[num_keys] = ~0;      //< Set the last hash to 0xFFFF

                // Move collisions pointer to the unsorted_indexes.
                indexes += max_keys;

                //< Add the newest string to the end.
                indexes[num_keys] = num_keys;

                //Print (table);
                //printf ("Done inserting.\n");
                return num_keys;
            }

            // But we still don't know if the string is a new collision.

            //printf ("Checking if it's a collision... ");

            if (strcmp (key, keys - key_offsets[index]) != 0) {
                // It's a new collision!
                //printf ("It's a new collision!\n");

                if (value < 3)
                {
                    //printf ("Buffer overflow!\n");
                    return kRecordOverflow;
                }

                // Get offset to write the key too.
                value = key_offsets[num_keys - 1] + key_length + 1;

                byte collision_index = unsorted_indexes[mid];
                //printf ("\n\ncollision_index: %u", collision_index);

                CopyString (keys - value, key);
                //printf ("Inserting value: %u into index:%u "
                //        "num_keys:%u with other collision_index: %u\n", value, 
                //        index, num_keys, collision_index);
                key_offsets[num_keys] = value;

                pile_size = table->pile_size;
                indexes[mid] = static_cast<byte> (pile_size);
                indexes[num_keys] = static_cast<byte> (pile_size);

                // Insert the collision into the collision table.
                temp_ptr = &collission_list[pile_size];
                // Move collisions pointer to the unsorted_indexes.
                indexes += max_keys;
                *temp_ptr = collision_index;
                ++temp_ptr;
                *temp_ptr = num_keys;
                ++temp_ptr;
                *temp_ptr = ~0;
                table->pile_size = pile_size + 3;
                //< Added one term-byte and two indexes.

                // Add the newest key at the end.
                indexes[num_keys] = num_keys;

                // Set the last hash to 0xFFFF
                hashes[num_keys] = ~0;

                table->num_keys = num_keys + 1;

                //Print (table);

                //printf ("Done inserting.\n");
                // Then it was a collision so the table doesn't contain s.
                return num_keys;
            }
            //printf ("table already contains the key\n");
            return index;
        }
    }

    // The hash was not in the table.

    value = key_offsets[num_keys - 1] + key_length + 1;
    destination = keys - value;

    //printf ("The hash 0x%x was not in the table so inserting %s into mid:"
    //        " %i at index %u before hash 0x%x \n", hash, key, mid, 
    //        destination - reinterpret_cast<char*> (table), hashes[mid]);

    // First copy the string and set the key offset.
    CopyString (destination, key);
    key_offsets[num_keys] = value;

    // Second move up the hashes and insert at the insertion point.
    hash16_t* hash_ptr = hashes + num_keys;
    //*test = hashes;
    //printf ("l_numkeys: %u, hashes: %u hash_ptr: %u insert_ptr: %u\n", 
    //        num_keys, hashes - reinterpret_cast<hash16_t*> (table), 
    //        hash_ptr - reinterpret_cast<hash16_t*> (table), hashes + mid - 
    //        reinterpret_cast<hash16_t*> (table));
    hashes += mid;
    //Print (table);
    while (hash_ptr > hashes) {
        *hash_ptr = *(hash_ptr - 1);
        --hash_ptr;
    }
    *hashes = hash;

    // Mark as not having any collisions.
    indexes[num_keys] = kNoCollidingRecords;

    // Move up the sorted indexes and insert the unsorted index (which is 
    // the current num_keys).
    indexes += max_keys + mid;
    temp_ptr = indexes + num_keys;

    while (temp_ptr > indexes) {
        *temp_ptr = * (temp_ptr - 1);
        --temp_ptr;
    }
    *temp_ptr = num_keys;      //unsorted_indexes[mid] = num_keys;

    table->num_keys = num_keys + 1;

    //Print (table);
    //printf ("Done inserting.\n");
    //PrintLine ();

    return num_keys;
}

static byte TableFind (const Table* table, const char* key) {
    if (table == nullptr)
        return 0;
    //PrintLineBreak ("Finding record...", 5);
    index index,
        num_keys = table->num_keys,
        max_keys = table->max_keys,
        temp;

    if (key == nullptr || num_keys == 0)
        return kInvalidRecord;

    uint16_t size = table->size;

    const hash16_t* hashes = reinterpret_cast<const hash16_t*>
                             (reinterpret_cast<const byte*> (table) + 
                              sizeof (Table));
    const uint16_t* key_offsets = reinterpret_cast<const uint16_t*>(hashes +
                                                                    max_keys);
    const byte* indexes = reinterpret_cast<const byte*>(key_offsets +
                                                        max_keys),
        *unsorted_indexes = indexes + max_keys,
        *collission_list = unsorted_indexes + max_keys;
    const char* keys = reinterpret_cast<const char*> (table) + size - 1;
    const byte* collisions,
        *temp_ptr;

    hash16_t hash = Hash16 (key);

    //printf ("\nSearching for key \"%s\" with hash 0x%x\n", key, hash);

    if (num_keys == 1)
    {
        ////printf ("Comparing keys - key_offsets[0] - this %u\n%s\n", keys - 
        //        key_offsets[0] - reinterpret_cast<char*> (table), keys - 
        //        key_offsets[0]);
        if (strcmp (key, keys - key_offsets[0]) != 0) {
            //printf ("Did not find key %s\n", key);
            return kInvalidRecord;
        }
        //printf ("Found key %s\n", key);
        //PrintLine ();
        return 0;
    }

    // Perform a binary search to find the first instance of the hash the 
    // binary search yields. If the mid is odd, we need to subtract the 
    // sizeof (hash16_t*) in order to get the right pointer address.
    int low = 0,
        mid,
        high = num_keys - 1;

    while (low <= high) {
        mid = (low + high) >> 1;    //< >> 1 to /2

        hash16_t current_hash = hashes[mid];
        //printf ("low: %i mid: %i high %i hashes[mid]:%x\n", low, mid, 
        //         high, hashes[mid]);

        if (current_hash > hash) {
            high = mid - 1;
        }
        else if (current_hash < hash) {
            low = mid + 1;
        } else {
            // Duplicate hash found.
            //printf ("\nFound same hash at mid:%i hash:%x offset for key: "
            //        "%s\n", mid, hashes[mid], key);

            // Check for collisions

            collisions = reinterpret_cast<const byte*>(key_offsets) +
                max_keys * sizeof (uint16_t);
            index = collisions[mid];

            if (index < kNoCollidingRecords)
            {
                // There was a collision so check the table.
                //printf ("There was a collision so check the table\n");

                // The collisionsList is a sequence of indexes terminated by
                // an invalid index > kMaxNumOperations. collissionsList[0] is an 
                // invalid index, so the collisionsList is searched from 
                // lower address up.

                temp = indexes[mid];

                temp_ptr = collission_list + temp;
                index = *temp_ptr;
                while (index < kMaxNumOperations) {
                    //printf ("comparing to \"%s\"\n", keys - 
                    //        key_offsets[index]);
                    if (strcmp (key, keys - key_offsets[index]) == 0) {
                        //printf ("but table already contains key at offset:"
                        //        "%u.\n", index);
                        return index;
                    }
                    ++temp_ptr;
                    index = *temp_ptr;
                }
                //printf ("Did not find %s.\n", key);
                return kInvalidRecord;
            }

            // There were no collisions.

            // But we still don't know if the string is new or a collision.

            // Move collisions pointer to the unsorted indexes.
            indexes += max_keys;
            index = unsorted_indexes[mid];

            //printf ("\n!!!mid: %i-%x unsorted_indexes: %u key: %s\n"
            //        "hash: %x\n", mid, hashes[mid], index, keys - 
            //        key_offsets[index], Hash16 (keys - 
            //        key_offsets[index]));

            if (strcmp (key, keys - key_offsets[index]) != 0) {
                //< It was a collision so the table doesn't contain s.
                //printf (" but it was a collision and did not find key.\n");
                return kInvalidRecord;
            }

            //printf ("and found key at mid: %i\n", mid);
            return index;
        }
    }
    //printf ("Did not find a hash for key %s\n", key);
    //PrintLine ();

    return kInvalidRecord;
}

inline void TablePrint (Table* table) {
    if (table == nullptr) return;
    byte num_keys = table->num_keys,
        max_keys = table->max_keys,
        collision_index,
        temp;
    uint16_t size = table->size,
        pile_size = table->pile_size;
    PrintLine ('_');
    //printf ("| Table: %p\n| num_keys: %u max_keys: %u  "
    //        "pile_size: %u  size: %u", table, num_keys,
    //        max_keys, pile_size, size);
    //putchar ('\n');
    //putchar ('|');
    //for (int i = 0; i < 79; ++i) putchar ('_');
    //putchar ('\n');

    hash16_t* hashes = reinterpret_cast<hash16_t*>(reinterpret_cast<byte*>(table) +
                                                   sizeof (Table));
    uint16_t* key_offsets = reinterpret_cast<uint16_t*>(hashes + max_keys);
    byte* indexes = reinterpret_cast<byte*> (key_offsets + max_keys),
        *unsorted_indexes = indexes + max_keys,
        *collission_list = unsorted_indexes + max_keys,
        *cursor;
    char* keys = reinterpret_cast<char*> (table) + size - 1;

    //printf ("| %3s%10s%8s%10s%10s%10s%10s%11s\n", "i", "key", "offset",
    //        "hash_e", "hash_u", "hash_s", "index_u", "collisions");
    //putchar ('|');
    //for (int i = 0; i < 79; ++i)
    //    putchar ('_');
    //putchar ('\n');

    for (int i = 0; i < max_keys; ++i) {
        // Print each record as a row.
        // @todo Change max_keys to num_keys after done debugging.
        collision_index = indexes[i];
        //printf ("| %3i %9s %7u %9x %9x %9x %9u %10u: ", i,
        //        keys - key_offsets[i], key_offsets[i],
        //        Hash16 (keys - key_offsets[i]),
        //        hashes[unsorted_indexes[i]], hashes[i],
        //        unsorted_indexes[i], collision_index);

        if (collision_index != kNoCollidingRecords && i < num_keys) {
            // Print collisions.
            cursor = &collission_list[collision_index];
            temp = *cursor;
            ++cursor;
            //printf ("%u", temp);
            while (temp != kNoCollidingRecords) {
                temp = *cursor;
                ++cursor;
                if (temp == kNoCollidingRecords)
                    break;
                //printf (", %u", temp);
            }
        }

        //putchar ('\n');
    }
    //putchar ('|');
    //for (int i = 0; i < 79; ++i) putchar ('_');
    //putchar ('\n');

    //PrintMemory (table, table->size);
    //putchar ('\n');
}

}       //< namespace _