class HashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [[] for _ in range(size)]

    def _hash(self, key):
        return hash(key) % self.size

    def insert(self, key, value):
        index = self._hash(key)
        for pair in self.table[index]:
            if pair[0] == key:
                pair[1] = value
                return
        self.table[index].append([key, value])

    def find(self, key):
        index = self._hash(key)
        for pair in self.table[index]:
            if pair[0] == key:
                return pair[1]
        return None

    def delete(self, key):
        index = self._hash(key)
        for i, pair in enumerate(self.table[index]):
            if pair[0] == key:
                del self.table[index][i]
                return True
        return False

    def display(self):
        for i, bucket in enumerate(self.table):
            print(f"Index {i}: {bucket}")

hash_table = HashTable()

while True:
    print("\n1. Insert\n2. Find\n3. Delete\n4. Display\n5. Exit")
    ch = int(input("Enter choice: "))
    if ch == 1:
        size = int(input("Enter total entries: "))
        for _ in range(size):
            key = input("Enter key: ")
            value = input("Enter value: ")
            hash_table.insert(key, value)
        hash_table.display()
    elif ch == 2:
        key = input("Enter key to find: ")
        print(f"Find {key}:", hash_table.find(key))
    elif ch == 3:
        key = input("Enter key to delete: ")
        hash_table.delete(key)
    elif ch == 4:
        hash_table.display()
    elif ch == 5:
        break
    else:
        print("Invalid choice, try again.")