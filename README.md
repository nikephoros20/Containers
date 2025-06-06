# s21_containers

Библиотека, реализующая основные стандартные контейнерные классы языка С++.

Групповая разработка, полный список участников доступен по запросу.

Список классов: `list` (список), `map` (словарь), `queue` (очередь), `set` (множество), `stack` (стек), `vector` (вектор).

Дополнительные классы: `array` (массив), `multiset` (мультимножество).

Помимо этого, классы дополнены следующими функциями:

| Modifiers      | Definition                                      | Containers |
|----------------|-------------------------------------------------| -------------------------------------------|
| `iterator insert_many(const_iterator pos, Args&&... args)`          | Inserts new elements into the container directly before `pos`.  | List, Vector. |
| `void insert_many_back(Args&&... args)`          | Appends new elements to the end of the container.  | List, Vector, Queue, Stack. |
| `void insert_many_front(Args&&... args)`          | Appends new elements to the top of the container.  | List. |
| `vector<std::pair<iterator,bool>> insert_many(Args&&... args)`          | Inserts new elements into the container.  | Map, Set, Multiset. |

