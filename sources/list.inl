//Arquivo de corpo list.inl

List<T>::List() {
	this->data = NULL;
}

void List<T>::push(T* data,int position){
    List<T> * current = this;
    while(current->next != NULL && position > 1){
       current = current->next;
       position--;
    }
    List<T> *aux = new List();
    *aux = *current;
    current->data = data;
    current->next = aux;
}


void List<T>::push(T* data){
    List<T> * current = this;
    while(current->next != NULL){
       current = current->next;
    }
    current->data = data;
    current->next = new List();
}

void List<T>::pop(int position){
    List<T> * current = this;
    List<T> * before = this;
    while(curren->next != NULL && position > 1){
        before = current;
        current = current->next;
        position--;
    }
    before->next = curren->next;
}

T* List<T>::get(int pos) {
	List<T> * current = this;
    while(current->next != NULL && position > 1){
       current = current->next;
       position--;
    }
    return current->data;
}

List::~List() {
    //dtor
}
