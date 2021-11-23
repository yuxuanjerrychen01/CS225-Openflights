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

######################################################################### updated Nov. 23rd

file = "./airports_data_useful.csv"
useful_df = pd.read_csv(file, encoding="utf_8_sig")
temp_df = useful_df.isnull().any(axis=1)
# index is all data that have cities as NaN
index = useful_df.index[temp_df]

drop_city_df = useful_df.drop(index=index)
# check if cities with NaN have been dropped
temp_df = drop_city_df.isnull().any(axis=1)
index2 = drop_city_df.index[temp_df]
# print(index2)

df_ICAO_null_info = drop_city_df.loc[useful_df["ICAO"] == "\\N"]
# index == 5860 is where "Sun Island Resort and SPA" data is. Will drop this unique ICAO-null data
# print(df_ICAO_null_info)
# print(drop_city_df.iloc[5860])
drop_city_ICAO_df = drop_city_df.drop(index=5860)
# print(drop_city_ICAO_df)
drop_city_ICAO_df.to_csv("./airports_data_useful_drop_city_ICAO.csv", index=False, encoding="utf_8_sig")

# check that NaN cities and null ICAO data have been dropped
temp_df = drop_city_ICAO_df.isnull().any(axis=1)
index3 = drop_city_ICAO_df.index[temp_df]
# print(index3)
# print("Sun Island Resort and SPA" in drop_city_ICAO_df.values)

# get all airports with names that do not finish with "Airport"
names_df = drop_city_ICAO_df.loc[~drop_city_ICAO_df["Name"].str.contains("Airport")]
names_df.to_csv("./airports_data_useful_nonAirport.csv", index=False, encoding="utf_8_sig")
index4 = names_df.index
# print(index4)
# print(drop_city_ICAO_df.iloc[9])

# consider dropping these data?
drop_city_ICAO_nonAirport_df = drop_city_ICAO_df.drop(index=index4)
# names_df = drop_city_ICAO_nonAirport_df.loc[~drop_city_ICAO_nonAirport_df["Name"].str.contains("Airport")]
# print(names_df)
drop_city_ICAO_nonAirport_df.to_csv("./airports_data_useful_drop_city_ICAO_nonAirport.csv",
                                    index=False, encoding="utf_8_sig")

# get all airports with names that do not "Airport" and the following substrings
names2_df = names_df.loc[(~names_df["Name"].str.contains("Base")) &
                         (~names_df["Name"].str.contains("Heliport")) &
                         (~names_df["Name"].str.contains("Airfield")) &
                         (~names_df["Name"].str.contains("RAF")) &
                         (~names_df["Name"].str.contains("Air Field")) &
                         (~names_df["Name"].str.contains("Air Station")) &
                         (~names_df["Name"].str.contains("CFB")) &
                         (~names_df["Name"].str.contains("Airbase")) &
                         (~names_df["Name"].str.contains("Air Force")) &
                         (~names_df["Name"].str.contains("Airstrip")) &
                         (~names_df["Name"].str.contains("Facility"))]
names2_df.to_csv("./airports_data_useful_nonAirport_improved.csv", index=False, encoding="utf_8_sig")
