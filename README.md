# Memory managements and templates mini project

## Opis

Ten dokument przedstawia szczegółową dokumentację klasy `DynArray`, która jest dynamiczną tablicą zarządzającą pamięcią oraz zestaw testów jednostkowych sprawdzających jej poprawność.

## Klasa `DynArray`

### Deklaracja Klasy

```cpp
template<typename T>
class DynArray {
private:
    T* data;
    int capacity;
    int length;

public:
    DynArray();
    ~DynArray();
    int size();
    bool isEmpty();
    void clear();
    void reserve(int newCapacity);
    void add(const T& element);
    void removeAt(int index);
    const T& operator[](int index) const;
};
```

### Składowe Prywatne

- `T* data`: Wskaźnik na dynamicznie alokowaną tablicę elementów
- `int capacity`: Pojemność tablicy, czyli maksymalna liczba elementów, które mogą być przechowywane bez realokacji pamięci.
- `int length`: Aktualna liczba elementów w tablicy.

### Metody Publiczne

#### Konstruktor Domyślny

```cpp
DynArray() {
    data = nullptr;
    capacity = 0;
    length = 0;
}
```

Inicjalizuje pustą tablicę.

#### Destruktor

```cpp
~DynArray() {
    delete[] data;
}
```

Zwalnia dynamicznie alokowaną pamięć.

#### `size()`

```cpp
int size() {
    return length;
}
```

Zwraca liczbę elementów w tablicy.

#### `isEmpty()`

```cpp
bool isEmpty() {
    return length == 0;
}
```

Sprawdza, czy tablica jest pusta.

#### `clear()`

```cpp
void clear() {
    length = 0;
}
```

Usuwa wszystkie elementy z tablicy.

#### `reserve(int newCapacity)`

```cpp
void reserve(int newCapacity) {
    if (newCapacity <= capacity) {
        return;
    }

    T* newData = new T[newCapacity];

    for (int i = 0; i < length; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}
```

Rezerwuje pamięć dla co najmniej `newCapacity` elementów.

#### `add(const T& element)`

```cpp
void add(const T& element) {
    if (length >= capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        reserve(newCapacity);
    }
    data[length++] = element;
}
```

Dodaje element do tablicy, zwiększając pojemność, jeśli jest to konieczne.

#### `removeAt(int index)`

```cpp
void removeAt(int index) {
    if (index < 0 || index >= length) {
        return;
    }
    for (int i = index; i < length - 1; i++) {
        data[i] = data[i + 1];
    }
    length--;
}
```

Usuwa element z tablicy na podanym indeksie i przesuwa pozostałe elementy.

#### Operator `[]`

```cpp
const T& operator[](int index) const {
    return data[index];
}
```

Zwraca referencję do elementu na podanym indeksie.

## Testy Jednostkowe

### Testy dla Klasy `DynArray`

#### Sprawdzanie, czy tablica jest pusta po utworzeniu

```cpp
TEST(DynArrayTests, EmptyArray) {
    DynArray<int> arr;
    EXPECT_EQ(0, arr.size());
    EXPECT_EQ(true, arr.isEmpty());
}
```

#### Dodawanie dwóch elementów i ich dostęp

```cpp
TEST(DynArrayTests, AddingElements) {
    DynArray<int> arr;
    arr.add(42);
    arr.add(24);
    EXPECT_EQ(2, arr.size());
    EXPECT_EQ(42, arr[0]);
    EXPECT_EQ(24, arr[1]);
}
```

#### Usuwanie elementów

```cpp
TEST(DynArrayTests, RemovingElements) {
    DynArray<int> arr;
    arr.add(42);
    arr.add(24);
    EXPECT_EQ(2, arr.size());
    arr.removeAt(0);
    EXPECT_EQ(24, arr[0]);
}
```

#### Czyszczenie tablicy

```cpp
TEST(DynArrayTests, ClearAllElements) {
    DynArray<int> arr;
    arr.add(42);
    arr.add(24);
    EXPECT_EQ(2, arr.size());
    arr.clear();
    EXPECT_EQ(0, arr.size());
}
```

#### Dodawanie elementów w pętli

```cpp
TEST(DynArrayTests, AddElementsInFor) {
    DynArray<int> arr;
    for(int i = 0; i < 1024; ++i) {
        arr.add(i);
    }
}
```

#### Rezerwowanie pamięci z wyprzedzeniem

```cpp
TEST(DynArrayTests, ReserveMemoryUpfront) {
    DynArray<int> arr;
    arr.reserve(1024);
    for(int i = 0; i < 1024; ++i) {
        arr.add(i);
    }
}
```

## Podsumowanie

Klasa `DynArray` oferuje dynamicznie rosnącą tablicę z zarządzaniem pamięcią. Dzięki metodzie `reserve`, możliwe jest zminimalizowanie liczby realokacji. Testy jednostkowe weryfikują poprawność operacji takich jak dodawanie, usuwanie i czyszczenie elementów, zapewniając stabilność i niezawodność implementacji.
