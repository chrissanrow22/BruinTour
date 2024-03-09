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
private:
	struct Node {
		std::string m_key;
		T m_value;
		Node* next;
	};

	int m_numAssociations;
	double m_maxLoadFactor;
	std::vector<Node*> m_buckets;

	// Returns whether adding a new association would cause the hash table to exceed
	// the maximum load factor
	bool exceedsMaxLoadFactor() const;

	int hashItem(const std::string key) const;
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
	int keyHashVal = hashItem(key);
	//search for string hash in associated linked list in vector, and update
	//if found. if not found insert new key value pair into vector

	// traverse linked list associated with hash to find key
	Node* p = m_buckets[keyHashVal];
	while (p != nullptr && p->m_key != key) {
		p = p->next;
	}
	//key does not yet have an association
	if (p == nullptr) {
		p = new Node;
		p->m_key = key;
	}
	//update / set value
	p->m_value = value;

	m_numAssociations++;
}

template <typename T>
T* HashMap<T>::find(const std::string& key) const {
	int keyHashVal = hashItem(key);

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
	int keyHashVal = hashItem(key);

	Node* p = m_buckets[keyHashVal];
	while (p != nullptr && p->m_key != key) {
		p = p->next;
	}
	// key was found
	if (p != nullptr) {
		return p->m_value;
	}
	// key was not found
	p = new Node;
	p->m_key = key;
	m_numAssociations++;
	return p;
}

//HELPER FUNCTIONS

template <typename T>
bool HashMap<T>::exceedsMaxLoadFactor() const {
	double resultantLoadFactor = (m_numAssociations + 1) / m_buckets.size();
	return resultantLoadFactor > m_maxLoadFactor;
}

template <typename T>
int HashMap<T>::hashItem(const std::string key) const {
	return (std::hash<std::string>()(key)) % m_buckets.size();
}