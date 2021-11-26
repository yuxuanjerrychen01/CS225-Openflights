import pandas as pd

file = "routes_data.txt"
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

