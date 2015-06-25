#ifndef MaoListDoublyLinked_included
#define MaoListDoublyLinked_included


//valid order begins with 0


namespace Mao{

	template<typename KeyType>
	class MaoListDoublyLinkedNode
	{
	public:

		MaoListDoublyLinkedNode * prev;

		KeyType key;

		MaoListDoublyLinkedNode * next;
	};

	template<typename KeyType>
	class MaoListDoublyLinked //with loop
	{
	public:
		MaoListDoublyLinked();//(bool autoRelease = false);
		~MaoListDoublyLinked();

		int Add(const KeyType key, int afterOrder = -1);		//after the order in this list

		// can use just if what i store is not an Object, or class of the Objest has overrided '==' operation - 2015.06.25
		int Insert(const KeyType key, const KeyType afterKey);	//after the first Key existing in this list

		bool Delete(const int order);

		// can use just if what i store is not an Object, or class of the Objest has overrided '==' operation - 2015.06.25
		KeyType Remove(const int order, bool * result = nullptr);

		// can not deal with Compile Time Error temporarily - 2015.06.25
		//bool RemoveAll();	// whth Release key. Should be used when the key is a pointer to stack
		
		bool Clear();		// without Release key

		// can use just if what i store is not an Object, or class of the Objest has overrided '==' operation - 2015.06.25
		int GetOrder(const KeyType key);

		KeyType& GetKey(const int order, bool * result = nullptr);

	private:
		void insertRelation(MaoListDoublyLinkedNode<KeyType> *& afterNode,
			MaoListDoublyLinkedNode<KeyType> *& newNode);

	private:
		//bool autoRelease;	// auto delete ptr in destruction
		int count;			// not include my head
		MaoListDoublyLinkedNode<KeyType> head;
	};











	template<typename KeyType>
	MaoListDoublyLinked<KeyType>::MaoListDoublyLinked()//(bool autoRelease = false)
	{
		count = 0;
		//this->autoRelease = autoRelease;

		head.prev = &head;
		head.next = &head;
	}

	template<typename KeyType>
	MaoListDoublyLinked<KeyType>::~MaoListDoublyLinked()
	{
		// can not deal with Compile Time Error temporarily - 2015.06.25
		//if (true == autoRelease)
		//	RemoveAll();
		//else

		Clear();
	}

	template<typename KeyType>
	int MaoListDoublyLinked<KeyType>::Add(const KeyType key, int afterOrder = -1)		//after the order in this list
	{
		int newPosRET = 0;
		MaoListDoublyLinkedNode<KeyType> * afterNode = &head;
		if (afterOrder < -1)				// false, wrong afterOrder
			return -1;
		else if (afterOrder >= count - 1)	// insert and become the last one
		{
			afterNode = head.prev;
			newPosRET = count + 1;
		}
		else if (-1 == afterOrder)		// insert and become the first one
			;//newPosRET = 0
		else							// find and insert
		{
			for (int i = -1; i < afterOrder; i++)
			{
				afterNode = afterNode->next;
				newPosRET++;
			}
		}


		MaoListDoublyLinkedNode<KeyType> * newNode = new MaoListDoublyLinkedNode<KeyType>;
		newNode->key = key;
		insertRelation(afterNode, newNode);

		count++;

		return newPosRET;
	}


	template<typename KeyType>
	int MaoListDoublyLinked<KeyType>::Insert(const KeyType key, const KeyType afterKey)		//after the first Key existing in this list
	{
		int newPosRET = 0;
		MaoListDoublyLinkedNode<KeyType> * checkNode = &head;
		while (&head != checkNode->next)
		{
			checkNode = checkNode->next;
			newPosRET++;
			if (checkNode->key == afterKey)
			{
				MaoListDoublyLinkedNode<KeyType> * newNode = new MaoListDoublyLinkedNode<KeyType>;
				newNode->key = key;
				insertRelation(checkNode, newNode);

				count++;

				return newPosRET;
			}
		}
		return -1;
	}

	template<typename KeyType>
	void MaoListDoublyLinked<KeyType>::insertRelation(MaoListDoublyLinkedNode<KeyType> *& afterNode,
		MaoListDoublyLinkedNode<KeyType> *& newNode)
	{
		newNode->prev = afterNode;
		newNode->next = afterNode->next;
		afterNode->next = newNode;
		newNode->next->prev = newNode;
	}


	template<typename KeyType>
	bool MaoListDoublyLinked<KeyType>::Delete(const int order)
	{
		bool ret = false;
		this->Remove(order, &ret);
		return ret;
	}

	template<typename KeyType>
	KeyType MaoListDoublyLinked<KeyType>::Remove(const int order, bool * result = nullptr)
	{
		if (order < 0 || order >= count)	// false, wrong afterOrder
		{
			if (nullptr != result) *result = false;
			return -1;
		}

		MaoListDoublyLinkedNode<KeyType> * targetNode = &head;
		for (int i = -1; i < order; i++)
			targetNode = targetNode->next;

		targetNode->prev->next = targetNode->next;
		targetNode->next->prev = targetNode->prev;

		KeyType ret = targetNode->key;

		delete targetNode;
		count--;

		if (nullptr != result) *result = true;
		return ret;
	}


	// can not deal with Compile Time Error temporarily - 2015.06.25
	//template<typename KeyType>
	//bool MaoListDoublyLinked<KeyType>::RemoveAll()	// whth Release
	//{
	//	MaoListDoublyLinkedNode<KeyType> * toDeleteNode = nullptr;
	//	while (0 != count)
	//	{
	//		toDeleteNode = head.next;
	//		head.next = head.next->next;

	//		delete toDeleteNode->key;

	//		delete toDeleteNode;
	//		count--;
	//	}
	//	return true;
	//}

	template<typename KeyType>
	bool MaoListDoublyLinked<KeyType>::Clear()		// without Release
	{
		MaoListDoublyLinkedNode<KeyType> * toDeleteNode = nullptr;
		while (0 != count)
		{
			toDeleteNode = head.next;
			head.next = head.next->next;

			delete toDeleteNode;
			count--;
		}
		return true;
	}

	template<typename KeyType>
	int MaoListDoublyLinked<KeyType>::GetOrder(const KeyType key)
	{
		MaoListDoublyLinkedNode<KeyType> * toDeleteNode = &head;
		for (int i = count; i > 0; i--)
		{
			toDeleteNode = toDeleteNode->next;
			if (key == toDeleteNode->key)
				return count - i; //key's order ( count + 1 - i - 1)
		}
		return -1;
	}

	template<typename KeyType>
	KeyType& MaoListDoublyLinked<KeyType>::GetKey(const int order, bool * result)
	{
		if (order < 0 || order >= count)
		{
			if (nullptr != result) *result = false;
			return -1;
		}

		MaoListDoublyLinkedNode<KeyType> * find = &head;
		int check = order;
		while (check >= 0)
		{
			find = find->next;
			check--;
		}

		return find->key;
	}


}

#endif