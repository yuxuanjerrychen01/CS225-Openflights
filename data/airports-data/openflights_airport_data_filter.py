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

##############################################
# new part, deleted all airport row data where there was no mention of such airport in airlines data (no source airport, no destiniation airport)

file1 = "./airports_data_useful_drop_city_ICAO_nonAirport.csv"
df1 = pd.read_csv(file1)
file2 = "../routes_data_final.csv"
df2 = pd.read_csv(file2)

airports_id = df1["Airport ID"]
source_id = df2["Source Airport ID"]
dest_id = df2["Destination Airport ID"]
# print(airports_id)
# print(source_id)
# print(dest_id)

check_duplicates1 = source_id.duplicated()
if True in check_duplicates1.values:
    source_id.drop_duplicates(inplace=True)

check_duplicates2 = dest_id.duplicated()
if True in check_duplicates2.values:
    dest_id.drop_duplicates(inplace=True)

# print(source_id)
# print(dest_id)

source_list = source_id.tolist()
dest_list = dest_id.tolist()
airports_list = airports_id.tolist()



airports_list_1 = airports_list.copy()
airports_list_2 = airports_list.copy()
airports_list_3 = airports_list.copy()
airports_list_4 = airports_list.copy()
for i in range(len(source_list)):
    for j in range(len(airports_list_1)):
        if airports_list_1[j] == source_list[i]:
            airports_list_1[j] = -7

for i in range(len(dest_list)):
    for j in range(len(airports_list_1)):
        if airports_list_1[j] == dest_list[i]:
            airports_list_1[j] = -7

print(len(airports_list))
removed_neither = list(filter((-7).__ne__, airports_list_1))
print(removed_neither)
print(len(removed_neither))

# source airport not exist
# for i in range(len(source_list)):
#     for j in range(len(airports_list_2)):
#         if airports_list_2[j] == source_list[i]:
#             airports_list_2[j] = -7
#
# print(len(airports_list))
# removed_source = list(filter((-7).__ne__, airports_list_2))
# print(removed_source)
# print(len(removed_source))
#
# # dest sirport not exist
# for i in range(len(dest_list)):
#     for j in range(len(airports_list_3)):
#         if airports_list_3[j] == dest_list[i]:
#             airports_list_3[j] = -7
#
# print(len(airports_list))
# removed_dest = list(filter((-7).__ne__, airports_list_3))
# print(removed_dest)
# print(len(removed_dest))

# airports that have source or dest
# for i in range(len(airports_list)):
#     for j in range(len(removed_neither)):
#         if airports_list_4[i] == removed_neither[j]:
#             airports_list_4[i] = -8
#
# print(len(airports_list))
# new_airports_list = list(filter((-8).__ne__, airports_list_4))
# print(new_airports_list)
# print(len(new_airports_list))


file3 = "./airports_data_useful_drop_city_ICAO_nonAirport.csv"
df3 = pd.read_csv(file1)
print(df3)
# for i in range(len(removed_neither)):
#
#     df3 = df3.drop
sub_df = df3.loc[df3['Airport ID'].isin(removed_neither)]
print(sub_df)
index = sub_df.index
remove_df = df3.drop(index=index)
print(remove_df)
remove_df.to_csv("../airports_data_final_new.csv", index=False, encoding="utf_8_sig")
