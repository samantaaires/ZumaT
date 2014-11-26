//Arquivo de corpo list.inl

template <class T>
List<T>::List(){
    size = 0; //Define uma lista vazia;
    head = new Node<T>();
}

template <class T>
void List<T>::push(T* data, int position){ //Insere na posição
    Node<T> * current = this->head; //current é um auxiliar que recebe os "atributos    " da cabeça, para poder percorrer a lista.
    while(current->next != NULL && position > 1){
       current = current->next;
       position--;
    }
    Node<T> *aux = new Node<T>(); //auxiliar para ajudar na "troca" de posição. Para ajudar na inserção do valor na lista.
    *aux = *current; 
    current->data = data;
    current->next = aux; 
    this->size++; //Aumenta o tamanho da fila.
}

template <class T>
void List<T>::push(T* data){ //Isere no final.
    Node<T> * current = this->head;
    while(current->next){ //Verifica até chegar ao último nó da lista.
       current = current->next;
    }
    current->data = data; //Insere o dado.
    current->next = new Node<T>(); //Cria um novo nó vazio.
    this->size++; //Aumenta o tamanho da fila.
}

template <class T>
void List<T>::pop(){
    Node<T> * current = this->head;
    while(current->next){
       current = current->next;
    }
    current = NULL; //Remove os atributos do primeiro.
    this->size--; //Diminui o tamanho da lista.
}

template <class T>
void List<T>::pop(int position){ //Remove da posição.
    Node<T> * before = NULL; //Tem o anterior, pois terá que verificar os itens da direita e esquerda da lista.
    Node<T> * current = this->head;
    while(current->next && position > 1){ //Vai percorrendo a lista até a posição.
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
    this->size--; //Diminui o tamanho da lista.
}

template <class T>
T* List<T>::get(int position) { //Retorna o valor da posição.
	Node<T> * current = this->head;
    while(current->next != NULL && position > 1){
       current = current->next;
       position--;
    }
    return current->data;
}

template <class T>
int List<T>::length(){ //Retorna o tamanho da lista.
    return size;
}