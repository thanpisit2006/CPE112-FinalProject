# cpe112
CPE112 Final Project - Smart Inventory and Recommendation System implemented in C

hash id
modulo hash ต้องระบุ limit item (optimal)
id primary key
queue custumer a b c


verified commit test


GitHub workflow ที่ควรใช้

ก่อนเริ่มงาน
git pull

ทุกครั้งหลังแก้เสร็จ
git add .
git commit -m "add a condition that can't input negetive products qty"
git push

ถ้าจะดูประวัติ commit
git log --oneline

ถ้าต้องการ revert กลับ commit เก่า
ดู commit id:
git log --oneline

แล้ว:
git checkout <commit-id>

ดึงข้อมูลโค้ดจากทุกไฟล์
rm -f note.txt

find . -type f \
! -name "note.txt" \
! -path "./.git/*" \
! -name "*.o" \
! -name "*.exe" \
! -name "app" \
| sort | while read file
do
    echo "$file" >> note.txt
    echo '```' >> note.txt
    cat "$file" >> note.txt
    echo -e '\n```' >> note.txt
    echo >> note.txt
done

compile:
gcc src/*.c -Iinclude -Wall -Wextra -o app

run:
./app