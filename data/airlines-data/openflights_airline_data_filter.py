import pandas as pd

# input data.txt, output data.csv
file = "airlines.dat.txt"
test = pd.read_csv(file, delimiter=",", encoding="utf_8")
test.to_csv("./airlines_data.csv", index=False, encoding="utf_8_sig")

# obtain dataframe from data.csv
file = "airlines_data.csv"
df = pd.read_csv(file)

# check duplicates
check_duplicates = df.duplicated()
if True in check_duplicates.values:
    df.drop_duplicates(inplace=True)

# get the columns that have NaN values
temp_df = df.isnull().any()
column_list_NaN = df.columns[temp_df]
print(column_list_NaN)

# # get the list of rows with NaN values
# temp_df = df.isnull().any(axis=1)
# index = df.index[temp_df]
# df_NaN = df.iloc[index, :].reset_index(drop=True)
# df_NaN.to_csv("./airlines_data_NaN.csv", index=False, encoding="utf_8_sig")

# output subset dataframe from original dataframe
useful_df = df[["Airline ID", "Name", "Country", "Active"]]
useful_df.to_csv("./airlines_data_useful.csv", index=False, encoding="utf_8_sig")

# # get the list of rows with NaN values
# temp_df = useful_df.isnull().any(axis=1)
# index = useful_df.index[temp_df]
# df_NaN = useful_df.iloc[index, :].reset_index(drop=True)
# df_NaN.to_csv("./airlines_data_useful_NaN.csv", index=False, encoding="utf_8_sig")

file = "airlines_data_useful.csv"
useful_df = pd.read_csv(file, encoding="utf_8_sig")
temp_df = useful_df.isnull().any(axis=1)
# index is all data that have NaN
index = useful_df.index[temp_df]
# print(index)

drop_NaN_df = useful_df.drop(index=index)
# check if all data with NaN have been dropped
temp_df = drop_NaN_df.isnull().any(axis=1)
index2 = drop_NaN_df.index[temp_df]
# print(index2)


# check if any columns of drop_NaN_df have \N
# other columns do not have \N
var1 = "\\N" in drop_NaN_df["Airline ID"]
var2 = "\\N" in drop_NaN_df["Name"]
var3 = "\\N" in drop_NaN_df["Country"]
var4 = "\\N" in drop_NaN_df["Active"]
# print(var1 and var2 and var3 and var4)
drop_NaN_df.to_csv("./airlines_data_useful_drop_NaN.csv", index=False, encoding="utf_8_sig")
