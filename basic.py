# 1. IMPORTS
import math
import sys

# 2. COMMENTS
# This is a single-line comment
"""
This is a multi-line string, often used as a multi-line comment 
or a docstring to explain functions and classes.
"""

# 3. VARIABLES AND DATA TYPES
integer_var = 10                  # int
float_var = 3.14                  # float
string_var = "Hello, Python!"     # str
boolean_var = True                # bool

# 4. DATA STRUCTURES (COLLECTIONS)
my_list = [1, 2, 3, "apple"]      # List: Mutable (changeable), ordered
my_tuple = (10, 20, 30)           # Tuple: Immutable (unchangeable), ordered
my_dict = {"name": "Alice", "age": 25} # Dictionary: Key-value pairs
my_set = {1, 2, 3, 3, 4}          # Set: Unique elements only, unordered

# 5. BASIC OPERATORS
addition = 5 + 3                  # Arithmetic: +, -, *, /, // (floor div), %, **
is_equal = (5 == 3)               # Comparison: ==, !=, >, <, >=, <=
logical = True and (not False)    # Logical: and, or, not

# 6. CONDITIONAL STATEMENTS (CONTROL FLOW)
if integer_var > 15:
    print("Greater than 15")
elif integer_var == 10:
    print("Exactly 10")           # This block will execute
else:
    print("Less than 10")

# 7. LOOPS
# For Loop (Iterating over a sequence using an f-string for formatting)
for item in my_list:
    print(f"List item: {item}")   

# While Loop (Runs as long as the condition is True)
counter = 0
while counter < 3:
    print(f"Counter is {counter}")
    counter += 1

# 8. FUNCTIONS
def calculate_area(radius=1.0):
    """Calculates the area of a circle with a default radius of 1.0."""
    return math.pi * (radius ** 2)

area = calculate_area(5.0)        # Overriding the default radius

# 9. CLASSES AND OBJECTS (OBJECT-ORIENTED PROGRAMMING)
class Dog:
    # Constructor method (initializes the object)
    def __init__(self, name, breed):
        self.name = name
        self.breed = breed
        
    # Instance method
    def bark(self):
        return f"{self.name} says Woof!"

my_dog = Dog("Buddy", "Golden Retriever")
print(my_dog.bark())

# 10. ERROR HANDLING (TRY / EXCEPT)
try:
    result = 10 / 0
except ZeroDivisionError as error_msg:
    print(f"Error caught: {error_msg}")
finally:
    print("This 'finally' block executes no matter what happens.")

# 11. LIST COMPREHENSIONS (A concise, 'Pythonic' way to create lists)
# Creates a list of squared numbers from 0 to 4
squares = [x ** 2 for x in range(5)] 

# 12. FILE HANDLING (CONTEXT MANAGERS)
# Using 'with' ensures the file is safely and automatically closed after use
with open("sample.txt", "w") as file:
    file.write("Learning Python basics!")
