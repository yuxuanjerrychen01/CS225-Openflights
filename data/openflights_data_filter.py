import pandas as pd

# input data.txt, output data.csv
file = "./airports.dat.txt"
test = pd.read_csv(file, delimiter=",", encoding="utf_8")
test.to_csv("./airports_data.csv", index=False, encoding="utf_8_sig")

# obtain dataframe from data.csv
file = "./airports_data.csv"
df = pd.read_csv(file)

# check duplicates
check_duplicates = df.duplicated()
if True in check_duplicates.values:
    df.drop_duplicates(inplace=True)

# get the columns that have NaN values
# the only column with NaN is "City"
temp_df = df.isnull().any()
column_list_NaN = df.columns[temp_df]
# print(column_list_NaN)

# get the list of rows with NaN values
temp_df = df.isnull().any(axis=1)
index = df.index[temp_df]
df_NaN = df.iloc[index, :].reset_index(drop=True)
df_NaN.to_csv("./airports_data_NaN_city.csv", index=False, encoding="utf_8_sig")

# output subset dataframe from original dataframe
useful_df = df[["Airport ID", "Name", "City", "Country", "IATA", "ICAO", "Latitude", "Longitude"]]
useful_df.to_csv("./airports_data_useful.csv", index=False, encoding="utf_8_sig")

# check \N of IATA and ICAO
df_IATA_null = useful_df.loc[useful_df["IATA"] == "\\N"]
df_ICAO_null = useful_df.loc[useful_df["ICAO"] == "\\N"]
df_IATA_null.to_csv("./airports_data_useful_null_IATA.csv", index=False, encoding="utf_8_sig")
df_ICAO_null.to_csv("./airports_data_useful_null_ICAO.csv", index=False, encoding="utf_8_sig")

# check if other columns have \N
# other columns do not have \N
var1 = "\\N" in useful_df["Airport ID"]
var2 = "\\N" in useful_df["Name"]
var3 = "\\N" in useful_df["City"]
var4 = "\\N" in useful_df["Country"]
var5 = "\\N" in useful_df["Latitude"]
var6 = "\\N" in useful_df["Longitude"]
# print(var1 and var2 and var3 and var4 and var5 and var6)
