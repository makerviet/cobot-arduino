# Mã nguồn mở Arduino dành cho Cobot
Cobot là sản phẩm robot giáo dục của Công ty Cổ phần ThingEdu.
Mã nguồn mở Arduino dành cho Cobot được phát triển và chia sẻ phi lợi nhuận bởi Maker Việt, với sự đồng hành từ ThingEdu.

## Hướng dẫn lắp ráp CoBot
[Xem video hướng dẫn](https://youtu.be/J4CTvk9BN0E?si=wKa1nySzxEhOEeIE)


## Sử dụng các chương trình mẫu
Đối với người dùng Arduino IDE, sử dụng chương trình mẫu trong thư mục *examples*. Đối với người dùng PlatformIO, sử dụng chương trình mẫu trong thư mục *pio*.
- **cobot_motors_test**: chương trình mẫu giúp các bạn tham khảo các hàm để điều khiển robot di chuyển (đi thẳng, đi lùi, rẽ trái, rẽ phải, dừng).
- **cobot_simple_line_following**: chương trình mẫu giúp các bạn tham khảo các hàm để đọc cảm biến hồng ngoại, cảm biến màu và xây dựng một thuật toán dò đường cơ bản.

Chọn board **ESP32C3 Dev Module** để build và nạp chương trình.

## Các vấn đề thường gặp
### 1. Không nạp được chương trình
- **Bước 1**: Ngắt hoàn toàn kết nối mạch khỏi nguồn pin và máy tính.
- **Bước 2**: Nhấn giữ nút flash (nút được khoanh đỏ trong hình dưới), đồng thời cắm lại cáp USB kết nối mạch với máy tính.
![](https://raw.githubusercontent.com/makerviet/cobot/main/documents/img/3.jpg)
- **Bước 3**: Nhả nút flash, tiến hành nạp chương trình như bình thường.
- **Bước 4**: Sau khi nạp chương trình thành công, ngắt nguồn mạch và kết nối lại để chương trình bắt đầu chạy.
### 2. Không xuất được giá trị qua Serial Monitor (Arduino IDE)
Vào menu ***Tools***, trỏ tới mục ***USB CDC On Boot***, chọn ***Enable***
![](https://raw.githubusercontent.com/makerviet/cobot/1eed924444022dfd935ee815f97b51728cb1fb5f/documents/img/2.png)