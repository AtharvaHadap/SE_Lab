class HashTable:
    def __init__(self, size, probing_type='linear'):
        self.size = size
        self.table = [None] * self.size
        self.count = 0
        self.probing_type = probing_type

    def _hash(self, number):
        return number % self.size

    def _resize(self):
        old_table = self.table
        self.size *= 2
        self.table = [None] * self.size
        self.count = 0
        for item in old_table:
            if item is not None:
                self.insert(item)

    def insert(self, number):
        if self.count >= 0.7 * self.size:
            self._resize()
        index = self._hash(number)
        original_index = index
        i = 1
        while self.table[index] is not None:
            if self.probing_type == 'linear':
                index = (index + 1) % self.size
            elif self.probing_type == 'quadratic':
                index = (original_index + i**2) % self.size
                i += 1
            if i >= self.size:
                raise RuntimeError("Hash table is full after resizing.")
        self.table[index] = number
        self.count += 1

    def display(self):
        for i, item in enumerate(self.table):
            if item is not None:
                print(f"Index {i}: {item}")


if __name__ == "__main__":
    table_size = int(input("Table size: "))
    probing_method = input("Probing method (linear/quadratic): ").strip().lower()
    ht = HashTable(table_size, probing_type=probing_method)
    num_clients = int(input("How many numbers to add? "))
    for _ in range(num_clients):
        number = int(input("Enter number: "))
        ht.insert(number)
    ht.display()