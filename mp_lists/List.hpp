/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
using namespace std;

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if(head_==NULL) return;
  ListNode* tmp=head_;
  while(head_!=NULL){
    head_ = tmp->next;
    delete tmp;
    tmp = head_;
  }
  return;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  if (head_ != NULL) {
    newNode -> next = head_;
    head_-> prev = newNode;
    head_=newNode;
  }
  if (tail_ == NULL) {
    newNode->prev=NULL;
    newNode->next=NULL;
    tail_ = newNode;
    head_= newNode;
  }
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode * newNode = new ListNode(ndata);
  /// @todo Graded in MP3.1
  if(tail_!=NULL){
    newNode->prev=tail_;
    tail_->next=newNode;
    tail_=newNode;
  }
  if (tail_==NULL){
    newNode->prev=NULL;
    newNode->next=NULL;
    tail_ = newNode;
    head_= newNode;

  }
  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  if(splitPoint<=1) return start;
  if(start==NULL) return NULL;
  ListNode * tmp = curr;
  //for (int i = 0; i < splitPoint && curr != NULL; i++) {
  for (int i = 0; i < splitPoint && curr->next != NULL ;i++) {
    tmp=curr;
    curr = curr->next;
  }
  if (curr != NULL && curr->prev != NULL) {
    tmp ->next = NULL;
    curr->prev = NULL;
  }
  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  if(head_==NULL) return;
  ListNode *curr=head_;
  ListNode *tmp;
  while(curr->next->next!=NULL){
    tmp=curr->next;
    curr->next=curr->next->next;
    curr->next->prev=curr;
    curr=curr->next;
    tail_->next=tmp;
    tmp->prev=tail_;
    tail_=tmp;
    tmp->next=NULL;
  }
  /// @todo Graded in MP3.1
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */

template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /*ListNode* prevNode, *nextNode;
  ListNode *curr=startPoint
  if(startPoint==NULL || endPoint==NULL) return;

  prevNode = curr->prev;
  nextNode = curr ->next;
  startPoint->next=prevNode;
  startPoint->prev=nextNode;
  return reverse(nextNode,endPoint);


 ListNode prev=startPoint;
  ListNode curr=startPoint->next;
  ListNode tmp=curr->next;
  while(curr!=NULL){
    curr->next=prev;
    prev->prev=curr;
    curr->prev=tmp;

    prev=curr;
    curr=tmp;*/
    if(startPoint==NULL||endPoint==NULL) return;
    //two temp pointer for linking list

    ListNode* prev = startPoint->prev;
    ListNode* next = endPoint->next;
    ListNode* tmp;
    ListNode* curr;
    curr = startPoint;
    while(curr!=next){
      //rotate myself
      tmp = curr->next;
      curr->next = curr->prev;
      curr->prev = tmp;
      curr = curr->prev;
    }
    startPoint->next = next;
    endPoint->prev = prev;
    if(prev!=NULL) prev->next = endPoint;
    if(next!=NULL) next->prev = startPoint;

    tmp = startPoint;
    startPoint = endPoint;
    endPoint = tmp;

  /// @todo Graded in MP3.2
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if (head_==NULL) return;
  ListNode * startPoint = head_;
	ListNode * endPoint = head_;
	while(endPoint != NULL)
	{
		for(int i = 0; i < n-1 && endPoint->next!=NULL; i++)
		{
			endPoint = endPoint->next;
		}
		reverse(startPoint, endPoint);
    if(startPoint->prev==NULL) head_=startPoint;
    if(endPoint->next==NULL) tail_=endPoint;
		startPoint = endPoint->next;
    endPoint = startPoint;
	}
  /// @todo Graded in MP3.2
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  ListNode *output=NULL;
  ListNode *dummy=NULL;

  while(first!= NULL && second!= NULL){
    if(first->data<second->data){
      if(output==NULL){
        output=first;
        dummy=output;
      } else {
        output->next=first;
        first->prev=output;
        output=output->next;
      }
      first=first->next;
    } else {
      if(output==NULL){
        output=second;
        dummy=output;
      } else {
        output->next=second;
        second->prev=output;
        output=output->next;
      }
      second=second->next;
    }
  }
  if(first==NULL &&second ==NULL) return NULL;
  if(first!=NULL && second==NULL) {
    output->next=first;
    first->prev=output;
  //  output=output->next;
  //  first=first->next;
  }
  if(second !=NULL && first ==NULL){
    output->next=second;
    second->prev=output;
  //  output=output->next;
  //  second=second->next;
  }
  return dummy;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength<=1) return start;
  ListNode* newStart=start;
  for(int i =0; i< chainLength/2; i++){
    newStart=newStart->next;
  }
  newStart->prev->next=NULL;
  newStart->prev=NULL;
  start = mergesort(start,chainLength/2);
  newStart = mergesort(newStart,chainLength-chainLength/2);
  return merge(start, newStart);
}
