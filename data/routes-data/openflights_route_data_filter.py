import pandas as pd

# input data.txt, output data.csv
file = "routes_data.txt"
test = pd.read_csv(file, delimiter=",", encoding="utf_8")
test.to_csv("./routes_data.csv", index=False, encoding="utf_8_sig")

# obtain dataframe from data.csv
file = "routes_data.csv"
df = pd.read_csv(file)

# check duplicates
check_duplicates = df.duplicated()
if True in check_duplicates.values:
    df.drop_duplicates(inplace=True)
