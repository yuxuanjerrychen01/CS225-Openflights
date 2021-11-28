import pandas as pd

file = "routes.dat.txt"
test = pd.read_csv(file, delimiter = ",", encoding = "utf_8")
test.to_csv("./routes_data.csv", index = False, encoding = "utf_8_sig")

file = "routes_data.csv"
df = pd.read_csv(file)

check_duplicates = df.duplicated()
if True in check_duplicates.values:
  df.drop_duplicates(inplace=True)
# print(df)

####################### checking NaN in columns
# df.columns
#Index(['Airline (IATA or ICAO)', 'Airline ID', 'Source Airport',
       #'Source Airport ID', 'Destination Airport', 'Destination Airport ID',
       #'Codeshare', 'Stops', 'Equipment'],
      #dtype='object')
Airline_subset = df[['Airline (IATA or ICAO)']]
Airline_subset.isna().sum()

Airline_id_subset = df[['Airline ID']]
Airline_id_subset.isna().sum()

Airline_source_airport = df[['Source Airport']]
Airline_source_airport.isna().sum()

Airline_source_id = df[['Source Airport ID']]
Airline_source_id.isna().sum()

Airline_destination = df[['Destination Airport']]
Airline_destination.isna().sum()

Airline_destination_id = df[['Destination Airport ID']]
Airline_destination_id.isna().sum()

Airline_codeshare = df[['Codeshare']]
print(Airline_codeshare.isna().sum())

Airline_stops = df[['Stops']]
Airline_stops.isna().sum()

Airline_equipment = df[['Equipment']]
Airline_equipment.isna().sum() 
#if we should drop the row with NaN equipment?
#df['Equipment'].fillna('None', inplace = True)
#Airline_equipment.isna().sum()

# the only two columns that have NaN are Codeshare and Equipment
####################### 

# all data (rows) with codeshare "Y"
codeshare_df = df.loc[df["Codeshare"] == "Y"]
codeshare_df.to_csv("./routes_data_codeshareY.csv", index=False, encoding="utf_8_sig")

# all data (rows) with stops > 0 (stops == 1)
stops1_df = df.loc[~(df["Stops"] == 0)]
stops1_df.to_csv("./routes_data_stops1.csv", index=False, encoding="utf_8_sig")

# all data (rows) with stops == 0
stops0_df = df.loc[(df["Stops"] == 0)]
stops0_df.to_csv("./routes_data_stops0.csv", index=False, encoding="utf_8_sig")

# drop Codeshare column, Stops column, and Equipment column
useful_df = stops0_df[
    ["Airline (IATA or ICAO)", "Airline ID", "Source Airport", "Source Airport ID", "Destination Airport",
     "Destination Airport ID"]]
useful_df.to_csv("./routes_data_useful_stops0.csv", index=False, encoding="utf_8_sig")


#########################################
# finding any data row that has \N

file = "routes_data_useful_stops0.csv"
df1 = pd.read_csv(file)
df2 = df1["Destination Airport ID"]

# index of data with \N in Destination Airport ID
df22 = df2.loc[df1["Destination Airport ID"] == "\\N"]
index = df22.index
# print(index)
drop_des_df = df1.drop(index=index)
# get all data that have Destination Airport ID as \N
temp_df = df1.loc[df1["Destination Airport ID"] == "\\N"]
temp_df.to_csv("./routes_data_useful_stops0_desAirportNull.csv", index=False, encoding="utf_8_sig")

df3 = drop_des_df["Source Airport ID"]
# index of data with \N in Source Airport ID
df33 = df3.loc[drop_des_df["Source Airport ID"] == "\\N"]
index = df33.index
drop_sou_des_df = drop_des_df.drop(index=index)
# print(drop_sou_des_df)
drop_sou_des_df.to_csv("./routes_data_useful_stops0_airportNoNull.csv", index=False, encoding="utf_8_sig")

df4 = drop_sou_des_df["Airline ID"]
# index of data with \N in Airline ID
df44 = df4.loc[drop_sou_des_df["Airline ID"] == "\\N"]
index = df44.index
# print(index)
drop_air_sou_des_df = drop_sou_des_df.drop(index=index)
# print(drop_air_sou_des_df)
drop_air_sou_des_df.to_csv("./routes_data_final.csv", index=False, encoding="utf_8_sig")

# check remaining columns
df5 = drop_air_sou_des_df["Airline (IATA or ICAO)"]
# index of data with \N in Airline
df55 = df5.loc[drop_air_sou_des_df["Airline (IATA or ICAO)"] == "\\N"]
index = df55.index
print(index)

df6 = drop_air_sou_des_df["Source Airport"]
# index of data with \N in Source Airport
df66 = df6.loc[drop_air_sou_des_df["Source Airport"] == "\\N"]
index = df66.index
print(index)

df7 = drop_air_sou_des_df["Destination Airport"]
# index of data with \N in Destination Airport
df77 = df7.loc[drop_air_sou_des_df["Destination Airport"] == "\\N"]
index = df77.index
print(index)

# we found out that for some data without airport ID, we could still obtain airport info trough IATA. Currently will still delete the rows, but will be considered.
# print(drop_air_sou_des_df.loc[drop_air_sou_des_df["Destination Airport"] == 12087])

