/*
#include <string>
#include <vector>
#include <list>
#include <functional>

template <typename T>
class HashMap
{
public:
	HashMap(double max_load = 0.75); // constructor  
	~HashMap(); // destructor; deletes all of the items in the hashmap  
	int size() const; // return the number of associations in the hashmap  
	// The insert method associates one item (key) with another (value).   
	// If no association currently exists with that key, this method inserts   
	// a new association into the hashmap with that key/value pair. If there is   
	// already an association with that key in the hashmap, then the item   
	// associated with that key is replaced by the second parameter (value).   
	// Thus, the hashmap must contain no duplicate keys.  
	void insert(const std::string& key, const T& value);
	// If no association exists with the given key, return nullptr; otherwise,   
	// return a pointer to the value associated with that key. This pointer can be   
	// used to examine that value or modify it directly within the map.  
	T* find(const std::string& key) const;
	// Defines the bracket operator for HashMap, so you can use your map like this: 
	// your_map["david"] = 2.99; 
	// If the key does not exist in the hashmap, this will create a new entry in  
	// the hashmap and map it to the default value of type T. Then it will return a 
	// reference to the newly created value in the map.  
	T& operator[](const std::string& key);

	//FIXME: is this the correct way to disallow copies or assingments
	HashMap(const HashMap&) = delete;
	HashMap& operator=(const HashMap&) = delete;

private:
	struct Node { //FIXME: how to initialize values of m_value and m_next
		std::string m_key;
		T m_value;
		Node* m_next;
	};

	int m_numAssociations;
	double m_maxLoadFactor;
	std::vector<Node*> m_buckets;

	// Returns whether adding a new association would cause the hash table to exceed
	// the maximum load factor
	bool exceedsMaxLoadFactor() const;

	//hashing functions
	//return the hash value for the given string
	int hashItem(const std::string key, int size) const;
	//rehash items in bucket and include new pairing
	void rehashToNewHashMap();
};

template <typename T>
HashMap<T>::HashMap(double max_load)
//Initialize hashmap with 10 buckets and 0 associations
	: m_buckets(std::vector<Node*>(10, nullptr)), m_numAssociations(0), m_maxLoadFactor(max_load)
{
}

template <typename T>
HashMap<T>::~HashMap() {
	//Iterate over vector and delete dynamically allocated linked lists
	for (int i = 0; i < m_buckets.size(); i++) {
		if (m_buckets[i] != nullptr) {
			delete m_buckets[i];
		}
	}
}

template <typename T>
int HashMap<T>::size() const {
	return m_numAssociations;
}

template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value) {
	int keyHashVal = hashItem(key, m_buckets.size());
	//search for string hash in associated linked list in vector, and update
	//if found. if not found insert new key value pair into vector

	//if there is an existing association for that hash value
	//check if the key already exists in the map
	if (m_buckets[keyHashVal] == nullptr) {
		//no association -> allocate new node
		m_buckets[keyHashVal] = new Node;
		m_buckets[keyHashVal]->m_next = nullptr;
		m_buckets[keyHashVal]->m_key = key;
		m_buckets[keyHashVal]->m_value = value;
		m_numAssociations++;
		if (exceedsMaxLoadFactor()) {
			rehashToNewHashMap();
		}
		return;
	}

	// if there is an association, traverse linked list associated with hash to find key
	Node* p = m_buckets[keyHashVal];
	while (p->m_next != nullptr && p->m_key != key) {
		p = p->m_next;
	}

	//key does not yet have an association -> allocate new node
	if (p->m_key != key) {
		//allocate new node for key
		p->m_next = new Node;
		p = p->m_next;
		//set node's next to nullptr since it's end of list
		p->m_next = nullptr;
		//update next node's key
		p->m_key = key;
		m_numAssociations++;
	}
	//update / set value
	p->m_value = value;
	if (exceedsMaxLoadFactor()) {
		rehashToNewHashMap();
	}
}

template <typename T>
T* HashMap<T>::find(const std::string& key) const {
	int keyHashVal = hashItem(key, m_buckets.size());
	Node* p = m_buckets[keyHashVal];
	while (p != nullptr && p->m_key != key) {
		p = p->next;
	}
	// key was found
	if (p != nullptr) {
		return p->m_value;
	}
	// key was not found
	return nullptr;
}

template <typename T>
T& HashMap<T>::operator[](const std::string& key) {
	int keyHashVal = hashItem(key, m_buckets.size());

	//if no association is already made with that hash value:
	if (m_buckets[keyHashVal] == nullptr) {
		//allocate new node
		m_buckets[keyHashVal] = new Node;
		m_buckets[keyHashVal]->m_next = nullptr;
		m_buckets[keyHashVal]->m_key = key;
		//default construct value
		m_buckets[keyHashVal]->m_value = T();

		m_numAssociations++;
		if (exceedsMaxLoadFactor()) {
			rehashToNewHashMap();
		}
		return m_buckets[keyHashVal]->m_value;
	}

	//if there is an existing association for that hash value
	//check if the key already exists in the map
	Node* p = m_buckets[keyHashVal];
	while (p->m_next != nullptr && p->m_key != key) {
		p = p->m_next;
	}

	//key does not yet have an association -> allocate new node
	if (p->m_key != key) {
		//allocate new node for key
		p->m_next = new Node;
		p = p->m_next;
		//set node's next to nullptr since it's end of list
		p->m_next = nullptr;
		//update next node's key
		p->m_key = key;
		//default construct value
		p->m_value = T();
		m_numAssociations++;

		if (exceedsMaxLoadFactor()) {
			rehashToNewHashMap();
		}
	}
	
	return p->m_value;

	//CORRECT VERSION

	T* val = find(key);
	if(find(key) == nullptr){
		insert(key, T());
		val = find(key);
	}
	return val;
}

//HELPER FUNCTIONS

template <typename T>
bool HashMap<T>::exceedsMaxLoadFactor() const {
	unsigned int resultantLoadFactor = m_numAssociations / m_buckets.size();
	return resultantLoadFactor > m_maxLoadFactor;
}

template <typename T>
int HashMap<T>::hashItem(const std::string key, int size) const {
	return (std::hash<std::string>()(key)) % size;
}

template <typename T>
void HashMap<T>::rehashToNewHashMap() {
	int newSize = m_buckets.size() * 2;
	//create new internal hash map with double the current number of buckets
	std::vector<Node*> newInternalHashMap(newSize, nullptr);

	//rehash all current items nad insert into new internal hashmap
	for (int i = 0; i < m_buckets.size(); i++) {
		//skip if no associations
		if (m_buckets[i] == nullptr) {
			continue;
		}

		//iterate over linked list of current bucket
		Node* p = m_buckets[i];
		while (p != nullptr) {
			//get key and value of current pair
			std::string currKey = p->m_key;
			T currVal = p->m_value;
			//obtain hash value from current key
			int currHash = hashItem(p->m_key, newSize);

			//if no association is already made with that hash value:
			if (newInternalHashMap[currHash] == nullptr) {
				//allocate new node
				newInternalHashMap[currHash] = new Node;
				newInternalHashMap[currHash]->m_next = nullptr;
				newInternalHashMap[currHash]->m_key = currKey;
				newInternalHashMap[currHash]->m_value = currVal;

				//proceed to next node in current linked list
				p = p->m_next;
				continue;
			}

			//otherwise, iterate over the corresponding bucket to find empty space to put pair

			Node* internalP = newInternalHashMap[currHash];
			while (internalP->m_next != nullptr) {
				internalP = internalP->m_next;
			}

			//insert pair into empty spot in internal hash map
			internalP->m_next = new Node;
			internalP = internalP->m_next;
			internalP->m_next = nullptr;
			internalP->m_key = currKey;
			internalP->m_value = currVal;

			//proceed to next node in current linked list
			p = p->m_next;
		}
	}

	//free memory of smaller hash map
	//FIXME: not sure if this is right
	for (int i = 0; i < m_buckets.size(); i++) {
		delete m_buckets[i];
	}
	//set m_buckets to newly created hashmap
	m_buckets = newInternalHashMap;
}
*/