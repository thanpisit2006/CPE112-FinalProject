# cpe112

Smart Convenience Management System

---

## overview

This project is a console-based inventory management system written in C.

The system supports:

- product management
- customer and admin login
- shopping cart system
- order queue system
- sales report
- recommendation system
- undo delete feature
- file persistence
- hash table for user management

---

## features

### admin features

- add product
- update product
- delete product
- undo deleted product
- sort products
- process customer orders
- view sales report
- manage stock

### customer features

- register and login
- browse products
- search product by id
- search product by name
- add product to cart
- checkout
- view recommended products

---

## data structures used

| data structure | usage |
|---|---|
| linked list | product storage |
| stack | undo deleted products |
| queue | customer orders |
| hash table | user management |

---

## project structure

```text
.
├── data/
│   ├── products.txt
│   ├── users.txt
│   ├── orders.txt
│   └── history.txt
│
├── include/
│   ├── cart.h
│   ├── file.h
│   ├── product.h
│   └── user.h
│
├── src/
│   ├── cart.c
│   ├── file.c
│   ├── main.c
│   ├── product.c
│   └── user.c
│
├── .gitignore
└── README.md


verified commit test


GitHub workflow ที่ควรใช้

ก่อนเริ่มงาน
git pull

ทุกครั้งหลังแก้เสร็จ
git add .
git commit -m "fix undo delete function"
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