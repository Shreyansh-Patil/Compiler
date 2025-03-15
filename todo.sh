dir="$1"
store="$2"

(echo -n > $store) # empty the file

j=1
temp=""

while IFS= read -r line; do
    # echo $line
    out=$(echo "$((echo $line) | awk -F"// TODO: " '{print $1}')")
    # echo $out
    count=0
    for (( i=((${#out} - 1)); i>=0; i-- )); do
        # echo "${out:i:1}"
        if [[ $(echo "${out:i:1}") == ":" ]]
        then
            ((count++))
            # echo "$count"
            continue
        fi
        
        if [[ $(echo "${out:i:1}") == "/" && "$count" == 1 ]]
        then
            # echo "${out:i:1}"
            ((count++))
            break
        fi

        if [[ "$count" == 1 ]]
        then
            # echo $temp
            temp="${out:i:1}${temp}"
        fi
    done
    # echo $temp
    (echo -n "$j [$temp] " >> $store)
    (echo "$((echo $line) | awk -F"// TODO: " '{print $2}')" >> $store)
    ((j++))
    temp=""
done < <(grep -r "// TODO: " "$dir" --exclude="todo.sh")