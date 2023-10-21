import random
import csv

# List of common Indian first names
indian_first_names = ["Aarav", "Aanya", "Aarush", "Advait", "Amara", "Anaya", "Aria", "Arjun", "Aryan", "Avani", "Dia", "Esha", "Ishaan", "Kabir", "Kiara", "Krishna", "Meera", "Neha", "Rahul", "Riya", "Rohan", "Sahil", "Shreya", "Tanvi", "Virat", "Zara"]

# List of common Indian surnames
indian_last_names = ["Sharma", "Verma", "Agarwal", "Singh", "Patel", "Reddy", "Kumar", "Choudhary", "Mehta", "Mishra", "Gupta", "Jain", "Yadav", "Bansal", "Malik", "Shah", "Pandey", "Dixit", "Kaur", "Shrivastava"]

# Number of random names to generate
num_names = 200

# Generate random names and write to a CSV file
with open("student.csv", "w", newline="") as csvfile:
    csv_writer = csv.writer(csvfile)
    csv_writer.writerow(["Name", "CET_percentile", "Category", "First_Priority", "Second_Priority"])
    
    for _ in range(num_names):
        name = random.choice(indian_first_names) + " " + random.choice(indian_last_names)
        cet_percentile = round(random.uniform(50.0, 99.9), 2)
        category = random.randint(1, 5)
        first_priority = random.randint(1, 4)
        second_priority = random.randint(1, 4)
        csv_writer.writerow([name, cet_percentile, category, first_priority, second_priority])
