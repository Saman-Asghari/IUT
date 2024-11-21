#include"AVL.h"


int max(int n1, int n2) {
	if (n1 >= n2)
		return n1;
	return n2;


}



template<typename T, typename V>
AVL_TREE<T, V>::AVL_TREE() {
	root = NULL;
	height = 0;
	assumed_null = new AVL_elem<T, V>;
	assumed_null->h = 0;
	count = 0;

};



template<typename T, typename V>
int AVL_TREE<T, V>::insert(V key, T* data) {
	if (count > 0) {
		if (find(key) != assumed_null)
			return 0;
	}
	//throw exeption

	AVL_elem<T, V>* new_elem = new AVL_elem<T, V>;
	new_elem->key = key;
	new_elem->data = data;
	if (root == NULL) {
		root = new_elem;
		root->p = assumed_null;
		root->l_c = assumed_null;
		root->r_c = assumed_null;
		root->h = 1;
		++count;
		return 0;
	}

	AVL_elem<T, V>* temp = root;
	AVL_elem<T, V>* temp_P = assumed_null;

	while (temp != assumed_null) {
		temp_P = temp;
		if (new_elem->key < temp->key)
			temp = temp->l_c;
		else
			temp = temp->r_c;
	}
	if (new_elem->key < temp_P->key) {
		temp_P->l_c = new_elem;
		new_elem->p = temp_P;
		new_elem->l_c = new_elem->r_c = assumed_null;
		new_elem->h = 1;

	}
	else {
		temp_P->r_c = new_elem;
		new_elem->p = temp_P;
		new_elem->l_c = new_elem->r_c = assumed_null;
		new_elem->h = 1;
	}

	//check balance and reset heights
	temp = new_elem->p;
	while (temp != assumed_null)
	{
		//after insetr temp->l_c->h=temp->r_c->h=temp->h-1 (no change is needed)
		if ((temp->l_c->h < temp->h) && (temp->r_c->h < temp->h))
			break;

		//beafore insetr temp->l_c->h=temp->r_c->h=temp->h-1
		if (temp->l_c->h == temp->h && temp->r_c->h == temp->h - 1) {
			temp->h += 1;
			temp = temp->p;
			continue;
		}
		if (temp->r_c->h == temp->h && temp->l_c->h == temp->h - 1) {
			temp->h += 1;
			temp = temp->p;
			continue;
		}
		//after insetr temp->l_c->h><temp->r_c->h =temp->h (restructer is needed)
		if (temp->l_c->h == temp->h) {
			if (temp->l_c->l_c->h == temp->l_c->h - 1) {
				r_rotate(temp);
				break;

			}
			else {
				l_rotate(temp->l_c);
				r_rotate(temp);
				break;
			}
		}
		else {

			if (temp->r_c->r_c->h == temp->r_c->h - 1) {
				l_rotate(temp);
				break;

			}
			else {
				r_rotate(temp->l_c);
				l_rotate(temp);
				break;
			}

		}

	}



	count++;
	return 1;

};



template<typename T, typename V>
AVL_elem<T, V>* AVL_TREE<T, V>::remove(V key) {
	AVL_elem<T, V>* n = find(key);
	if (n == assumed_null || count == 0)
		return NULL;
	AVL_elem<T, V>* temp = NULL;
	if (n->r_c == assumed_null || n->l_c == assumed_null) {
		if (n->r_c == assumed_null) {
			temp = n->l_c;
			temp->p = n->p;
			if (n->p->l_c == n) {
				n->p->l_c = temp;
			}
			else {
				n->p->r_c = temp;
			}

		}
		else if (n->l_c == assumed_null) {
			temp = n->r_c;
			temp->p = n->p;
			if (n->p->l_c == n) {
				n->p->l_c = temp;
			}
			else {
				n->p->r_c = temp;
			}

		}

		temp = temp->p;
		while (temp != assumed_null)
		{
			//no change is nedded
			if ((temp->l_c->h >= (temp->h - 2)) && (temp->r_c->h >= (temp->h - 2)))
				break;
			if ((temp->l_c->h == temp->r_c->h) && (temp->l_c->h == (temp->h - 2))) {
				temp->h--;
				temp = temp->p;
				continue;

			}
			if (temp->l_c->h == (temp->r_c->h - 2)) {
				l_rotate(temp);
				temp = temp->p->p;
				continue;


			}
			if (temp->r_c->h == (temp->l_c->h - 2)) {
				r_rotate(temp);
				temp = temp->p->p;
				continue;


			}

		}

		count--;
		return n;

	}
	else {
		AVL_elem<T, V>* s = successor(n);
		T* data = s->data;
		V k = s->key;
		s->data = n->data;
		s->key = n->key;
		n->data = data;
		n->key = k;
		return remove(s);
	}

}




template<typename T, typename V>
AVL_elem<T, V>* AVL_TREE<T, V>::remove(AVL_elem<T, V>* n) {

	AVL_elem<T, V>* temp = NULL;
	if (n->r_c == assumed_null || n->l_c == assumed_null) {
		if (n->r_c == assumed_null) {
			temp = n->l_c;
			temp->p = n->p;
			if (n->p->l_c == n) {
				n->p->l_c = temp;
			}
			else {
				n->p->r_c = temp;
			}

		}
		else if (n->l_c == assumed_null) {
			temp = n->r_c;
			temp->p = n->p;
			if (n->p->l_c == n) {
				n->p->l_c = temp;
			}
			else {
				n->p->r_c = temp;
			}

		}

		temp = temp->p;
		while (temp != assumed_null)
		{
			//no change is nedded
			if ((temp->l_c->h >= (temp->h - 2)) && (temp->r_c->h >= (temp->h - 2)))
				break;
			if ((temp->l_c->h == temp->r_c->h) && (temp->l_c->h == (temp->h - 2))) {
				temp->h--;
				temp = temp->p;
				continue;

			}
			if (temp->l_c->h == (temp->r_c->h - 2)) {
				l_rotate(temp);
				temp = temp->p->p;
				continue;


			}
			if (temp->r_c->h == (temp->l_c->h - 2)) {
				r_rotate(temp);
				temp = temp->p->p;
				continue;


			}

		}

		count--;
		return n;

	}
	else {
		AVL_elem<T, V>* s = successor(n);
		T* data = s->data;
		V k = s->key;
		s->data = n->data;
		s->key = n->key;
		n->data = data;
		n->key = k;
		return remove(s);
	}

}


template<typename T, typename V>
void AVL_TREE<T, V>::r_rotate(AVL_elem<T, V>* n) {
	AVL_elem<T, V>* temp;
	temp = n->l_c->r_c;
	n->l_c->p = n->p;
	if (n->p->l_c == n)
		n->p->l_c = n->r_c;
	else
		n->p->r_c = n->r_c;
	n->l_c->r_c = n;
	n->p = n->l_c;
	n->l_c = temp;
	temp->p = n;
	n->h = max(n->l_c->h, n->r_c->h) + 1;
	n->p->h = max(n->p->l_c->h, n->p->r_c->h) + 1;
	if (n == root)
		root = n->p;

};

template<typename T, typename V>
void AVL_TREE<T, V>::l_rotate(AVL_elem<T, V>* n) {
	AVL_elem<T, V>* temp;
	temp = n->r_c->l_c;
	n->r_c->p = n->p;
	if (n->p->l_c == n)
		n->p->l_c = n->r_c;
	else
		n->p->r_c = n->r_c;
	n->r_c->l_c = n;
	n->p = n->r_c;
	n->r_c = temp;
	temp->p = n;
	n->h = max(n->l_c->h, n->r_c->h) + 1;
	n->p->h = max(n->p->l_c->h, n->p->r_c->h) + 1;
	if (n == root)
		root = n->p;

};



template<typename T, typename V>
AVL_elem<T, V>* AVL_TREE<T, V>::find(V key) {
	AVL_elem<T, V>* temp = root;

	while (temp != assumed_null)
	{
		if (temp->key == key)
			break;

		if (key < temp->key)
			temp = temp->l_c;
		else
			temp = temp->r_c;

	}

	return temp;

};




template<typename T, typename V>
AVL_elem<T, V>* AVL_TREE<T, V>::successor(AVL_elem<T, V>* n) {
	AVL_elem<T, V>* temp = n->r_c;
	AVL_elem<T, V>* temp_p = assumed_null;
	while (temp != assumed_null)
	{
		temp_p = temp;
		temp = temp->l_c;
	}

	return temp_p;

}




template<typename T, typename V>
bool AVL_TREE<T, V>::is_empty() {

	if (count == 0)
		return true;
	return false;

}


template<typename T, typename V>
int AVL_TREE<T, V>::num_o_elements() {

	return count;
}



template<typename T, typename V>
vector<AVL_elem<T, V>*>* AVL_TREE<T, V>::elements() {
	vector<AVL_elem<T, V>*>* vec = new vector<AVL_elem<T, V>*>;
	if (root != assumed_null)
		return inorder_traversal(vec, root);


	return vec;

}


template<typename T, typename V>
vector<AVL_elem<T, V>*>* AVL_TREE<T, V>::inorder_traversal(vector<AVL_elem<T, V>*>* vec, AVL_elem<T, V>* elem) {
	if (elem->l_c != assumed_null)
		inorder_traversal(vec, elem->l_c);
	vec->push_back(elem);
	if (elem->r_c != assumed_null)
		inorder_traversal(vec, elem->r_c);


	return vec;

}