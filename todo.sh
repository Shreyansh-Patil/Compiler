dir="$0"
store="$1"

(echo -n > $store)

j=1

while IFS= read -r line; do

    location="$(echo $line | awk -F"// TODO" '{print $1}')"
    task="$(echo $line | awk -F"// TODO" '{print $2}')"

    location="${location:1:((${#location} - 2))}"
    task="${task:2:${#task}}"

    (echo -e "[ ] Task $j: { $task }\nLocation: [ $location ]\n" >> $store)
    ((j++))
    
done < <(find . -type f \( -name '*.cpp' -o -name '*.md' -or -name '*.txt' \) -exec grep 'TODO' {} +)