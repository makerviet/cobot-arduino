# Mã nguồn mở Arduino dành cho Cobot
Cobot là sản phẩm robot giáo dục của Công ty Cổ phần ThingEdu.
Mã nguồn mở Arduino dành cho Cobot được phát triển và chia sẻ phi lợi nhuận bởi Maker Việt, với sự đồng hành từ ThingEdu.

## Hướng dẫn lắp ráp CoBot
[Xem video hướng dẫn](https://youtu.be/J4CTvk9BN0E?si=wKa1nySzxEhOEeIE)


## Sử dụng các chương trình mẫu
Đối với người dùng Arduino IDE, sử dụng chương trình mẫu trong thư mục examples. Đối với PlatformIO, sử dụng chương trình mẫu trong thư mục Platform IO.
- cobot_motors_test: chương trình mẫu giúp các bạn tham khảo các hàm để điều khiển robot di chuyển (đi thẳng, đi lùi, rẽ trái, rẽ phải, dừng).
- cobot_simple_line_following: chương trình mẫu giúp các bạn tham khảo các hàm để đọc cảm biến hồng ngoại, cảm biến màu và xây dựng một thuật toán dò đường cơ bản.

Chọn board ESP32C3 Dev Module để build và nạp chương trình.

## Các vấn đề thường gặp
### Không nạp được chương trình
### Không xuất được giá trị qua Serial Monitor (Arduino IDE)