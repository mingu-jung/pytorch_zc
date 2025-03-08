# Loop over each .yml file and rename it
for file in *.yml; do
    mv -- "$file" "$file.disabled"
done

# To re-enable the files
# for file in *.yml.disabled; do
#     mv -- "$file" "${file%.disabled}"
# done
