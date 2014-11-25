template <class T>
List<T>::List(){
    size = 0;
    head = new Node<T>();
}

template <class T>
void List<T>::push(T* data, int position){
    Node<T> * current = this->head;
    while(current->next != NULL && position > 1){
       current = current->next;
       position--;
    }
    Node<T> *aux = new Node<T>();
    *aux = *current;
    current->data = data;
    current->next = aux;
    this->size++;
}

template <class T>
void List<T>::push(T* data){
    Node<T> * current = this->head;
    while(current->next){
       current = current->next;
    }
    current->data = data;
    current->next = new Node<T>();
    this->size++;
}

template <class T>
void List<T>::pop(){
    Node<T> * current = this->head;
    while(current->next){
       current = current->next;
    }
    current = NULL;
    this->size--;
}

template <class T>
void List<T>::pop(int position){
    Node<T> * before = NULL;
    Node<T> * current = this->head;
    while(current->next && position > 1){
        before = current;
        current = current->next;
        position--;
    }
    if ( before ) {
        before->next = current->next;
        delete current;
    } else {
        this->head = current->next;
        delete current;
    }
    this->size--;
}

template <class T>
T* List<T>::get(int position) {
	Node<T> * current = this->head;
    while(current->next != NULL && position > 1){
       current = current->next;
       position--;
    }
    return current->data;
}

template <class T>
int List<T>::length(){
    return size;
}