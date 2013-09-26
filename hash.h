

/*
 * This is a hash function to store words and their definitions.
 */
// This code takes a word (key) and returns the hash table index where the definition can be found.
int f(char *key,int array_size);


int insert_word_into_hashtable(int index, word_entry_t *pWordEntry);
int init_hash_table(void);
int dump_hashtable(void);
int lookupWordLower(char *pWord);
