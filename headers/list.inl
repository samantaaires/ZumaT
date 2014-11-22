template <class T>
List<T>::List(){}

template <class T>
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

template <class T>
void List<T>::push(T* data){
    List<T> * current = this;
    while(current->next != NULL){
       current = current->next;
    }
    current->data = data;
    current->next = new List();
}

template <class T>
void List<T>::pop(int position){
    List<T> * current = this;
    List<T> * before = this;
    while(current->next != NULL && position > 1){
        before = current;
        current = current->next;
        position--;
    }
    before->next = current->next;
}

template <class T>
T* List<T>::get(int position) {
	List<T> * current = this;
    while(current->next != NULL && position > 1){
       current = current->next;
       position--;
    }
    return current->data;
}

template <class T>
int List<T>::length(){
    int i = 0;
    List<T> current = this;
    while(current->next != NULL){
        current = current->next;
        i++;
    }
    return i;
}