BIRTHDATE="Jan 1, 2000"
Presents=10
BIRTHDAY=$(gdate -d "$BIRTHDATE" +%A)
echo ${BIRTHDAY}