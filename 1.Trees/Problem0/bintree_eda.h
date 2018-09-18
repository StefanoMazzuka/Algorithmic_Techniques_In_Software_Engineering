//
//  bintree_eda.h
//
//  Implementación de árboles binarios (con compartición de nodos)
//
//  Estructuras de Datos y Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 20/01/17.
//  Copyright (c) 2017 Alberto Verdejo. All rights reserved.
//

#ifndef bintree_eda_h
#define bintree_eda_h

#include <iostream>
#include <memory>   // shared_ptr, make_shared
#include <stdexcept>
#include <stack>
#include <vector>
#include <queue>

template <class T>
class bintree {
protected:
    /*
     Nodo que almacena internamente el elemento (de tipo T),
     y punteros al hijo izquierdo y derecho, que pueden ser
     nullptr si el hijo es vacío (no existe).
     */
    struct TreeNode;
    using Link = std::shared_ptr<TreeNode>;
    struct TreeNode {
        TreeNode(Link const& l, T const& e, Link const& r) : left(l), elem(e), right(r) {};
        T elem;
        Link left, right;
    };
    
    // constructora privada
    bintree(Link const& r) : raiz(r) {}
    
    // puntero a la raíz del árbol
    Link raiz;
    
public:
    // árbol vacío
    bintree() : raiz(nullptr) {}
    
    // árbol hoja
    bintree(T const& e) :
    raiz(std::make_shared<TreeNode>(nullptr, e, nullptr)) {}
    
    // árbol con dos hijos
    bintree(bintree<T> const& l, T const& e, bintree<T> const& r) :
    raiz(std::make_shared<TreeNode>(l.raiz, e, r.raiz)) {}
    
    // constructora por copia, operador de asignación y destructora por defecto
    
    // consultar si el árbol está vacío
    bool empty() const {
        return raiz == nullptr;
    }
    
    // consultar la raíz
    T const& root() const {
        if (empty()) throw std::domain_error("El arbol vacio no tiene raiz.");
        else return raiz->elem;
    }
    
    // consultar el hijo izquierdo
    bintree<T> left() const {
        if (empty()) throw std::domain_error("El arbol vacio no tiene hijo izquierdo.");
        else return bintree<T>(raiz->left);
    }
    
    // consultar el hijo derecho
    bintree<T> right() const {
        if (empty()) throw std::domain_error("El arbol vacio no tiene hijo derecho.");
        else return bintree(raiz->right);
    }
    
    
    // recorridos
    
    std::vector<T> preorder() const {
        std::vector<T> pre;
        preorder(raiz, pre);
        return pre;
    }
    
    std::vector<T> inorder() const {
        std::vector<T> in;
        inorder(raiz, in);
        return in;
    }
    
    std::vector<T> postorder() const {
        std::vector<T> post;
        postorder(raiz, post);
        return post;
    }
    
    std::vector<T> levelorder() const {
        std::vector<T> levels;
        if (!empty()) {
            std::queue<Link> pendientes;
            pendientes.push(raiz);
            while (!pendientes.empty()) {
                Link sig = pendientes.front();
                pendientes.pop();
                levels.push_back(sig->elem);
                if (sig->left != nullptr)
                    pendientes.push(sig->left);
                if (sig->right != nullptr)
                    pendientes.push(sig->right);
            }
        }
        return levels;
    }
    
protected:
    static void preorder(Link a, std::vector<T> & pre) {
        if (a != nullptr) {
            pre.push_back(a->elem);
            preorder(a->left, pre);
            preorder(a->right, pre);
        }
    }
    
    static void inorder(Link a, std::vector<T> & in) {
        if (a != nullptr) {
            inorder(a->left, in);
            in.push_back(a->elem);
            inorder(a->right, in);
        }
    }
    
    static void postorder(Link a, std::vector<T> & post) {
        if (a != nullptr) {
            postorder(a->left, post);
            postorder(a->right, post);
            post.push_back(a->elem);
        }
    }
    
public:
    // iterador que recorre el árbol en inorden
    class const_iterator {
    public:
        T const& operator*() const {
            if (ptr == nullptr) throw std::out_of_range("fuera del arbol");
            return ptr->elem;
        }
        T const* operator->() const {
            return &operator*();
        }
        
        bool operator==(const_iterator const& other) const {
            return ptr == other.ptr;
        }
        bool operator!=(const_iterator const& other) const {
            return !(*this == other);
        }
        
        const_iterator & operator++() {  // ++ prefijo
            next();
            return *this;
        }
        
    protected:
        friend class bintree;
        Link ptr;
        std::stack<Link> ancestros;
        
        const_iterator() : ptr(nullptr) {}
        const_iterator(Link act) { ptr = first(act); }
        
        Link first(Link act) {
            if (act == nullptr) {
                return nullptr;
            } else {
                while (act->left != nullptr) {
                    ancestros.push(act);
                    act = act->left;
                }
                return act;
            }
        }
        
        void next() {
            if (ptr == nullptr) {
                throw std::range_error("El iterador no puede avanzar");
            } else if (ptr->right != nullptr) {
                ptr = first(ptr->right);
            } else if (ancestros.empty()) {
                ptr = nullptr;
            } else {
                ptr = ancestros.top();
                ancestros.pop();
            }
        }
        
    };
    
    const_iterator begin() const {
        return const_iterator(raiz);
    }
    const_iterator end() const {
        return const_iterator();
    }
    
};


#endif // bintree_eda_h
