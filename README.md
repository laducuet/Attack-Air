# Game Attack Air
Game bắn máy bay dựa trên cảm hứng game trên điện thoại

1.	Hướng dẫn cài đặt:

   •	Clone code về từ link github
   
   •	Vào thư mục debug -> vào gamedemo.exe -> chơi thử game
   
2.	Mô tả chung về trò chơi, các ý tưởng chính:

   •	Các đối tượng có trong game :
   
      Nhân vật
      
      Kẻ thù
      
      Điểm số, thời gian
      
      Âm thanh 
      
      Sử dụng các thư viện của SDL
      
   •	Điều khiển máy bay bắn hạ các máy bay địch cho đến khi game over và nhận về số điểm của người chơi:
   
   •	Mỗi lượt chơi sẽ có 3 mạng và hiện thị tối đa trong màn hình là 3 máy bay địch.
   
   •	Mỗi lần bắn hạ được máy bay địch sẽ được cộng 1 điểm, điểm và thời gian chơi sẽ hiện trên màn hình
   
   •	Click chuột để bắn đạn, có thể dùng cả chuột trái và chuột phải để bắn ra 2 loại đạn khác nhau
   
   •	Dùng lên, xuống, sang để điều khiển nhân vật
   
3.	Các chức năng chính đã cài đặt

   •	File Common_Function.h : quản lý các biến toàn cục dùng cho cả chương trình và các hàm thực hiện việc load ảnh lên màn hình, hàm giải phóng bộ nhớ
   
   •	File BaseObject.h thực hiện việc định nghĩa lớp cha là BaseObject gồm các chức năng:
   
      Load hình ảnh của chính lớp đó vào màn hình 
      
      Quản lý việc xuất hiện trong màn hình của đối tượng
   •	File MainObject thực hiện việc định nghĩa lớp MainObject thừa kế của lớp BaseObject có chức năng :
   
      Định nghĩa ra đối tượng nhân vật chính để người chơi điều khiển 
      
   •	File AmoObject thực hiện việc định nghĩa lớp AmoObject thừa kế của lớp BaseObject có chức năng :
   
      Định nghĩa ra đối tượng đạn dược trong quá trình chiến đấu
      
   •	File ThreatsObject thực hiện việc định nghĩa lớp ThreatsObject thừ kế lớp BaseObject có chức năng :
   
      Định nghĩa ra đối tượng quân thù trong trò chơi
      
   •	File TextObject thực hiện việc định nghĩa lớp TextObject thừa kế lớp BaseObject có chức năng :
   
      Định nghĩa ra đối tượng TextObject để hiện thị thời gian và điểm số lên màn hình trò chơi
      
   •	File playpower.h thực hiện việc định nghĩa lớp playpower thừa kế lớp BaseObject có chức năng :
   
      Định nghĩa ra lớp quản lý số mạng của người chơi
      
   •	File ExplosionObject.h thực hiện việc định nghĩa lớp ExplosionObject thừa kế lớp BaseObject có chức năng :
   
      Thực hiện việc load hiệu ứng vụ nổ
   
   link demo game : https://youtu.be/FIjpTmD_3u0

4.	Các kĩ thuật lập trình được sử dụng

   •	Sử dụng các hàm trong thư viện SDL/SDL2
   
   •	Sử dụng chủ yếu là kĩ thuật lập trình hướng đối tượng để tạo ra các đối tượng trong trò chơi
   
   •	Sử dụng con trỏ và tham chiếu để tối ưu hóa bộ nhớ trong quá trình làm game
   
5.	Kết luận, hướng phát triển và các điều rút ra sau khi làm game

   •	Kết luận 
   
      Game sau khi đã hoàn thành có thể cho người dùng trải nghiệm, đây là 1 game cơ bản nhưng vẫn đầy đủ các chức năng cần thiết để người dùng có thế chơi 1 cách thoải mái nhất
      
   •	Hướng phát triển
   
      Mặc dù đã hoàn thiện nhưng vẫn còn 1 số thiếu sót và dưới đây là hướng hoàn thiện và phát triển tiếp theo của game :
      
        i.	Thực hiện được việc pause giữa game và hiện thị điểm số cao nhất của người chơi
        
       ii.	Sau khi load hết screen có thể tạo ra boss đánh nhau và đánh hoàn thành 1 màn chơi để tiếp tục sang màn tiếp theo.
       
      iii.	Các màn tiếp theo thì tốc độ các máy bay định nhanh hơn, map dài hơn và các boss mạnh hơn
      
       iv.	Tiếp tục tối ưu các biến trong game, không để biến cố định để người nâng cấp game có thể tiện sửa chữa và tăng độ khó
       
        v.	Tạo ra đối tượng các item để trò chơi thêm phần thú vị
        
   •	Điều tâm đắc sau khi hoàn thiện chương trình:
   
     Học được cách quản lý và liên kết các file trong 1 chương trình lớn
     
     Học cách lập trình hướng đối tượng
     
     Tối ưu hóa và clean code
     
     Cài các thư viện bên ngoài ide vào để thực hiện chương trình
     


