/**
 * 
 *         < Tạo từng thực thể riêng biệt để dễ dàng sửa chữa nếu có lỗi xảy ra + code gọn gàng >
 * 
 *      Thực thể: Sinh viên 
 *      Với các chức năng tương ứng gắn với nó, 
 *          Các mô tả chức năng sẽ được viết ở từng hàm
 *          Tổng quát chúng ta có:
 *      1. Struct Sinh viên -  chứa các thuộc tính 
 *                              "Mã số sinh viên - MSSV - kiểu int"
 *                              "Tên: họ, đệm, tên - kiểu mảng xâu ký tự" 
 *                              "Số tín chỉ - tin - kiểu int"
 *                              "Ngày sinh: Ngày/tháng/năm"
 *          ** CHỨC NĂNG PHỤ: 
 *                      + in danh sách sinh viên hiện có 
 *                      + in một sinh viên ra ngoài console 
 *                      + tìm một sinh viên theo MSSV
 *      2. Kiểm tra sự tồn tại của sinh viên trong file SV.bin (IN: MSSV, OUT: chỉ số thứ tự sinh viên trong file)
 *      3. Ghi file SV.bin = Bổ sung sinh viên (IN: sinh viên với đầy đủ thông tin (struct SinhVien)) 
 *      4. Xóa 1 sinh viên (IN: MSSV)
 *      TEST:  Cập nhật file SV.bin 
 *              + Bổ sung sinh viên 
 *              + Xóa sinh viên 
 *              + Cập nhật dữ liệu (vd thay đổi mã sinh viên, thay đổi tên sinh viên,...)
 *      
 *                      
**/
#ifndef SV_H
    #define SV_H
    #include <stdio.h>
    #include <string.h>
    #define fileSV  "D:\\Project_KTLT_C\\fileBin\\SV.bin"
    #define temp_fileSV "D:\\Project_KTLT_C\\fileBin\\temp_SV.bin"
    

    struct SinhVien{
        long MSSV;
        char ho[10];
        char dem[20];
        char ten[8];
        char gioiTinh[4];
        int ngaySinh;
        int thangSinh;
        int nam;
    };
    typedef struct SinhVien SV;
    
    ////////    PROTOTYPE FOR SV

    //  Chức năng phụ: kiểm tra sự tồn tại của SinhVien -> vị trí trong file

        int CheckExist_SV_toPosition(long MSSV);  

    //  Chức năng chính: Bổ sung/thêm một sinh viên vào file SV.bin

        void WriteSV_ToBIN (SV svien); 

    //  Chức năng chính: Xóa một sinh viên     

        int Delete_SV(long MSSV);  

    //  Chức năng chính: Cập nhật dữ liệu cho sinh viên  

        int Update_SV(long MSSV, SV new_svien);
 
    ///////////////////////////////////////////////////////////////////////////////////////////

    //Chức năng phụ: In danh sách sinh viên hiện có,   

        void Print_SV_bin();  
        void PrintHeaderFor_SV();
        //void FooterFor_NoSV();

    //Chức năng phụ: In thông tin 1 SV sẵn có   

        void PrintSV(SV svien, int position); 

    //Chức năng phụ: Tìm sinh viên trong file 

        SV FindSV(int position); /// có kiểm tra vị trị
        SV GetSV_withNoCheck(long MSSV); /// không kiểm tra 

    //Chức năng phụ: Thay đổi 1 SinhVien trong file

        int ChangeStruct_To_SV_bin(int position,SV new_svien);

    // Chức năng phụ: Kiểm tra có phải là 1 blank SV ??

        int IsBlank_SV(SV svien);   

    // Chức năng phụ: Đánh giá tính đúng đắn của ngày
    
        int IsValidDay(int ngay, int thang, int nam);      

    // Chức năng phụ: lấy dung lượng của file .bin hiện tại
    int GetSizeOf_bin(char fileName[]); 
    //
    //////////////////       END PROTOTYPE      ///////////////////////////////
    /**
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
    **/  
    //////////////////////      CODING         //////////////////////////////

    // Chức năng phụ: lấy dung lượng của HP.bin hiện tại

    int GetSizeOf_bin(char fileName[]){
        int sizeOfFile = 0;
        FILE *hpBin;
        hpBin = fopen(fileName,"rb");
        if(hpBin!=NULL){
            fseek(hpBin,0,SEEK_END);                /// đưa về vị trị cuối cùng của file bin
            sizeOfFile = ftell(hpBin);              /// sau đó dùng ftell(FILE*) để lấy dung lượng byte của file
            fseek(hpBin,0,SEEK_SET);            /// feof(file.bin) là không phù hợp với file bin nên cần phải lấy dung lượng data
        }else{
            printf("GetSizeOf_HP_bin: CANNOT OPEN File.bin!!\n");
            printf("%s\n",fileName);
            sizeOfFile = -1;
        }
        fclose(hpBin); 
        return sizeOfFile;   
    }
    // Chức năng phụ: Kiểm tra có phải là 1 blank SV ?? trả về 0 nếu true, -1 là false

    int IsBlank_SV(SV svien){
        if(svien.MSSV==0 && strcmp(svien.ho,"")==0 && strcmp(svien.dem,"")==0 && strcmp(svien.ten,"")==0 && strcmp(svien.gioiTinh,"")==0 && svien.ngaySinh==0 && svien.ngaySinh==0 && svien.nam==0){
            return 0;
        }else{
            return -1;
        }
    }

    // Chức năng phụ: Đánh giá tính đúng đắn của ngày, trả về 0 nếu là ngày hợp lệ

        int IsValidDay(int ngay, int thang, int nam){
            if(nam>=0){
                if(thang <1 || thang >12){
                    return -1;
                }else{
                    if(ngay==31){
                        if(thang!=2 && thang!=4 && thang!=6 && thang!=9 && thang!=11){
                            return 0;
                        }else{
                            return -1;
                        }
                    }else if(ngay==30){
                        if(thang==2){
                            return -1;
                        }else{
                            return 0;
                        }
                    }else if(ngay>31|| ngay<1){
                        return -1;
                    }else{
                        if(ngay==29 && thang ==2){
                            if((nam%400==0)||((nam%4==0) && nam%100!=0)){
                                return 0;
                            }else{
                                return -1;
                            }
                        }else{
                            return 0;
                        }
                    }    
                }       
            }else{
                return -1;
            }
            
        }

    void PrintHeaderFor_SV(){
        printf("+-----+----------------+-------------------------------------------+---------------+-------------+\n");
        printf("|%5s|%16s|%30s             |%15s|%11s  |\n"," "," ","Ten Sinh vien"," "," ");
        printf("|%4s |%12s    |------------+------------------+-----------|%12s   |%11s  |\n","STT","Ma so SV","Ngay sinh","Gioi tinh");
        printf("|%5s|%16s|%7s     |%10s        |%9s  |%15s|%11s  |\n"," "," ","Ho","Dem","Ten"," "," ");
        printf("+-----+----------------+------------+------------------+-----------+---------------+-------------+\n");
    }


    /**     Chức năng phụ : in danh sách sinh viên hiện có       **/
    void Print_SV_bin(){
        SV tempSv;
        int sizeOfFile = GetSizeOf_bin(fileSV);
        int count=0;
        FILE *svBin;

        printf("\n");
        printf("+------------------------------------------------------------------------------------------------+\n");
        printf("|\t\t\t\t%2s\t\t\t\t\t |\n","DANH SACH SINH VIEN HIEN CO");
        PrintHeaderFor_SV();
        
        svBin=fopen(fileSV,"rb");
        if(svBin!=NULL){
            while(ftell(svBin)<sizeOfFile){             
                fread(&tempSv, sizeof(SV),1,svBin);
                printf("|%3d  |%12d    |%10s  |%17s |%9s  |   %02d/%02d/%4d  |%8s     |\n"
                , ++count, tempSv.MSSV, tempSv.ho, tempSv.dem, tempSv.ten
                , tempSv.ngaySinh,tempSv.thangSinh,tempSv.nam,tempSv.gioiTinh);
                printf("+-----+----------------+------------+------------------+-----------+---------------+-------------+\n");
            }
        }else{
            printf("CANNOT OPEN FILE SV.bin\n");
        }
        fclose(svBin);
        
    }
    /**     Chức năng phụ: in sinh vien ra ngoài console|| IN: SinhVien nào đó**/
    void PrintSV(SV svien, int position){
        if(position !=-1){
            PrintHeaderFor_SV();
            printf("|%3d  |%12d    |%10s  |%17s |%9s  |   %02d/%02d/%4d  |%8s     |\n",position,svien.MSSV,svien.ho,svien.dem,svien.ten,svien.ngaySinh,svien.thangSinh,svien.nam,svien.gioiTinh);
            printf("+-----+----------------+------------+------------------+-----------+---------------+-------------+\n");
        }else{
            printf("NOT FOUND!!\n");
        }
            
    }

    /**
     *      Chức năng phụ: Thay thế SinhVien trên file
     * IN: vị trí sinh viên nằm ở file,
     *     sinh viên mới sẽ thay thế ở vị trí đó (nếu sinh viên mới rỗng thì sẽ xóa sinh viên tại vị trí đó)
     * OUT: 0 nếu việc thay đổi dữ liệu thành công, -1 nếu thất bại
     * - Nếu vị trí không tồn tại (<=-1) thì sẽ không tiến hành mà in thông báo file không có sự thay đổi gì
     *   Ngược lại
     *      Tiến hành duyệt file, 
     *              copy nội dung file từ đầu đến vị trí ta cần thay đổi sang file temp
     *              Đến vị trí cần xét, thực hiện đánh giá sinh viên đầu vào
     *              Nếu: Sinh vien đầu vào là 
     *                  rỗng => bỏ qua dòng đó và nhảy sang phần tử tiếp theo trong file
     *                          tiếp tục copy đến hết file
     *                  Không rỗng => thực hiện viết sinh viên vào file mới
     *                                sau đó tiếp tục copy file cũ đến hết
     * - Sau khi đã copy xong, tiến hành xóa file cũ + đổi tên file temp thành file SV.bin =>return 0
     * - Trong quá trình thực hiện, gặp bất kì sự cố nào sẽ break, return -1
    **/
    int ChangeStruct_To_SV_bin(int position,SV new_svien){
        FILE *svBin, *temp_svBin;
        SV exchangeSV;
        int sizeOfFile = GetSizeOf_bin(fileSV);
        int indexByte=0;

        if(position!=-1){
            svBin = fopen(fileSV,"rb");
            if(svBin!=NULL){
                temp_svBin = fopen(temp_fileSV,"wb");
                if(temp_svBin!=NULL){
                    while(indexByte<sizeOfFile){
                        if(indexByte!=(position-1)*sizeof(SV)){
                            fread(&exchangeSV,sizeof(SV),1,svBin);
                            fwrite((char*)&exchangeSV,sizeof(SV),1,temp_svBin);
                        }else{
                            if(IsBlank_SV(new_svien)!=0){
                                fwrite((char*)&new_svien,sizeof(SV),1,temp_svBin);
                            }
                            fseek(svBin,sizeof(SV),SEEK_CUR);
                        }
                        indexByte=ftell(svBin);
                    }
                }else{
                    printf("CANNOT OPEN FILE temp_SV.bin\n");
                }
                fclose(temp_svBin);
            }else{
                printf("CANNOT OPEN FILE SV.bin\n");
            }
            fclose(svBin);

        }else{
            printf("UNVALID POSITION, NOTHING CHANGES!!\n");
        }
        if(indexByte!=0){
            if(remove(fileSV)==0){
                rename(temp_fileSV,fileSV);
                return 0;
            }else{
                printf("UPDATE FAIL!!\n");
            }             /// trong quá trình xóa file, không được mở 2 file lên   
        }
        return -1;
    }

    /** ----------------------------------------------------------------------------------------------------------    
     *      2. Kiểm tra sự tồn tại của sinh viên theo thông tin: 
     * IN: Mã sinh viên,
     * OUT: thứ tự của sinh viên trong File hoặc thông báo chưa tồn tại
     *  - Tiến hành duyệt file, nếu file không mở được thì thông báo ra màn hình và không tiến hành các bước tiếp
     *  - Nếu thông tin về mã sinh viên trùng với yêu cầu
     *          In ra thông báo tồn tại và trả về vị trí của môn học trong file
     *    Nếu không thì trả về -1 và thông báo không tồn tại
     * -----------------------------------------------------------------------------------------------------------
    **/ 
    int CheckExist_SV_toPosition(long MSSV){
        SV tempSV={0,"","","","",0,0,0};
        int sizeOfFile = GetSizeOf_bin(fileSV);
        int count=0,result=0;
        FILE *svBin;

        svBin=fopen(fileSV,"rb");
        if(svBin!=NULL){
            while(ftell(svBin)<sizeOfFile){
                count++;
                fread(&tempSV, sizeof(SV),1,svBin);
                if(tempSV.MSSV==MSSV){
                    printf("THIS STUDENT: %ld EXISTED!!!!\n",MSSV);
                    result=count;
                    break;
                }
            }
            if((ftell(svBin)==sizeOfFile && result==0) || count==0){
                printf("THIS STUDENT: %ld DOESN'T EXIST!!\n",MSSV);
                result=-1;
            }
        }else{
            printf("CANNOT OPEN FILE SV.bin\n");
            result=-1;
        }
        fclose(svBin);
        return result;
    }
    /// Chức năng phụ: lấy được SV theo MSSV // nhưng phải đảm bảo là Sinh viên đó đã tồn tại
    SV GetSV_withNoCheck(long MSSV){
        SV svien={0,"","","","",0,0,0};
        FILE *svBin;
        int sizeOfFile = GetSizeOf_bin(fileSV);
        svBin = fopen(fileSV,"rb");
        if(svBin!=NULL){
            while(ftell(svBin)<sizeOfFile){
                fread(&svien,sizeof(SV),1,svBin);
                if(svien.MSSV==MSSV){
                    fclose(svBin);
                    break;
                }
            }
        }else{
            printf("GetSV_withNoCheck : CANNOT OPEN FILE SV.bin!!\n");
            fclose(svBin);
        }
        return svien;
    }
    /** ----------------------------------------------------------------------------------------------------------------
     *          Chức năng phụ:
     *                   Tìm kiếm sinh viên  
     * 
     *    IN: mảng xâu kí tự chứa nội dung là Mã sinh viên
     *    OUT: Một struct sinh viên
     *    - Tiến hành đọc file BIN, nếu file không mở được tiến hành báo lỗi còn không thì chạy bình thường
     *    - Tiến hành kiểm tra SinhVien đã tồn tại chưa
     *    - Nếu : tìm được mã sinh viên cần tìm 
     *               =>> thông báo tìm thấy, và in ra màn hình vị trí và thông tin SV, trả về sinh viên
     *      Trái lại:
     *              =>> thông báo không tồn tại, trả về sinh viên BLANK
     *    
     * ------------------------------------------------------------------------------------------------------------------         
    **/
    SV FindSV(int position){
        SV tempSV={0,"","","","",0,0,0};
        FILE *svBin;

        if(position!=-1){
            svBin=fopen(fileSV,"rb");
            if(svBin!=NULL){
                fseek(svBin,(position-1)*sizeof(SV),SEEK_SET);
                fread(&tempSV,sizeof(SV),1,svBin);
                //PrintSV(tempSV,position);
            }else{
                printf("CANNOT OPEN FILE SV.bin\n");
            }
            fclose(svBin);
        }else{
            printf("THIS OBJECT DOESN'T EXIST!!\n");
        }    
        return tempSV;
    }


    /** ------------------------------------------------------------------------------    
     *          3. Ghi sinh viên vào file SV.bin
     *  IN: sinh viên bất kỳ miễn là chưa tồn tại trong file
     *  - Tiến hành kiểm tra SV.bin xem trong file đã tồn tại sinh viên này hay chưa
     *  - Nếu đã tồn tại: 
     *          => In ra màn hình thông báo sinh viên đã tồn tại 
     *             và Không thêm vào file, thủ túc kết thúc
     *    Trái lại: 
     *          => Thêm vào file và in thông báo thành công
     * --------------------------------------------------------------------------------
    **/
    void WriteSV_ToBIN (SV svien){
        FILE *svBin;
        int position;

        svBin=fopen(fileSV,"ab");
        if(svBin!=NULL){
            if(CheckExist_SV_toPosition(svien.MSSV)==-1 && IsValidDay(svien.ngaySinh,svien.thangSinh,svien.nam)==0 && IsBlank_SV(svien)!=0){      //// nếu tồn tại thì hàm CheckExist_SV_toPosition sẽ in ra màn hình
                fwrite(&svien,sizeof(SV),1,svBin);
                printf("INSERT SUCCESSFULLY!!\n");
            }else{
                printf("PLEASE READ \"SV.bin\" AGAIN BEFORE INSERTING ANOTHER!!\n");
            }
        }else{
            printf("CANNOT OPEN FILE SV.bin\n");
        }
        fclose(svBin);

    }
    /**
     *          4. Xóa một sinh viên theo thông tin người dùng
     * IN: Mã số sinh viên cần xóa
     * OUT: 0 nếu xóa thành công, -1 nếu thất bại
     * - Tiến hành kiểm tra sự tồn tại của sinh viên
     *     -Nếu đã tồn tại, thủ tục kết thúc và báo lỗi
     *     -Nếu không, thì tiếp tục tiến trình và lấy kết quả vị trí sinh viên từ hàm CheckExist_SV_toPosition(long MSSV)
     * - Tiến hành thay thế vị trí đó trong file bởi 1 blank SV 
     * - Nếu xóa thành công sẽ hiển thị thông báo ra màn hình và in kết quả
     * 
    **/
    int Delete_SV(long MSSV){
        
        int position = CheckExist_SV_toPosition(MSSV);
        int status=-1;
        SV blankSV ={0,"","","","",0,0,0};

        if(position!=-1){
            status = ChangeStruct_To_SV_bin(position,blankSV);
            if(status!=0){
                printf("UNFORTUNATELY, DELETE \"%ld\" UNSUCCESSFULLY!!\n", MSSV);
            }else{
                printf("RESULT: \n");
                Print_SV_bin();
                printf("DELETE \"%ld\" SUCCESSFULLY!!\n", MSSV);
            }
        }else{
            printf("DELETE FAIL!!!\n");
            status = position;
        }
        return status;

    }

    /**
     *      5. Cập nhật dữ liệu cho sinh viên 
     * IN: MSSV cần cập nhật, một strucs Sinh viên mới
     * - Từ thông tin đầu vào, tiến hành kiểm tra trong file xem sinh viên đã tồn tại hay chưa??
     * - Nếu chưa tồn tại
     *        Ngừng hàm, báo lỗi chưa tồn tại ra màn hình
     *   Nếu đã tồn tại 
     *         Tiếp tục tiến hành các bước sau
     * - Kiểm tra liệu NDUng đầu vào liệu có làm lặp dữ liệu??
     *      Nếu có: trả về thông báo dữ liệu bị lặp nếu thay đổi, ngừng thủ tục
     *      Nếu không: Tiếp tục thực hiện
     * - Sau khi thực hiện thay đổi, 
     *      tiến hành thay thế sinh viên (thay trực tiếp tại file, tại dòng của sinh viên cũ)
     *      thông báo thay đổi thành công, và in ra màn hình danh sách hiện tại
     *      (Thông báo những thông tin đã được thay đổi)
     * 
    **/
    int Update_SV(long MSSV, SV new_svien){
        SV exchangeSV = {0,"","","","",0,0,0};
        int status = -1;
        int position = CheckExist_SV_toPosition(MSSV);
        int checkPositionOfNew = CheckExist_SV_toPosition(new_svien.MSSV);
        
        if(IsBlank_SV(new_svien)==0){
            printf("UPDATE FAIL!! YOU CAN'T SET A BLANK SV INTO FILE\n");
        }else{
            if(position!=-1){
                if(checkPositionOfNew == position || checkPositionOfNew == -1){
                    exchangeSV = FindSV(position);
                    if(exchangeSV.MSSV!=new_svien.MSSV && checkPositionOfNew==-1 && new_svien.MSSV!=0){
                        exchangeSV.MSSV = new_svien.MSSV;
                        printf("UPDATING..... %ld: MSSV => %ld\n",MSSV,exchangeSV.MSSV);
                    }
                    if(strcmp(new_svien.ho,"")!=0 && strcmp(new_svien.ho,exchangeSV.ho)!=0){
                        strcpy(exchangeSV.ho,new_svien.ho);
                        printf("UPDATING..... %ld: ho => %s\n",MSSV,exchangeSV.ho);
                    }
                    if(strcmp(new_svien.dem,"")!=0 && strcmp(new_svien.dem,exchangeSV.dem)!=0 ){
                        strcpy(exchangeSV.dem,new_svien.dem);
                        printf("UPDATING..... %ld: dem => %s\n",MSSV,exchangeSV.dem);
                    }
                    if(strcmp(new_svien.ten,"")!=0 && strcmp(new_svien.ten,exchangeSV.ten)!=0){
                        strcpy(exchangeSV.ten,new_svien.ten);
                        printf("UPDATING..... %ld: ten => %s \n",MSSV,exchangeSV.ten);
                    }
                    if(strcmp(new_svien.gioiTinh,"")!=0 && strcmp(exchangeSV.gioiTinh,new_svien.gioiTinh)!=0){
                        strcpy(exchangeSV.gioiTinh,new_svien.gioiTinh);
                        printf("UPDATING..... %ld: gioiTinh => %s\n",MSSV,exchangeSV.gioiTinh);
                    }
                    if(new_svien.ngaySinh!=0){
                        exchangeSV.ngaySinh=new_svien.ngaySinh;
                        printf("UPDATING..... %ld: ngaySinh => %d\n",MSSV,exchangeSV.ngaySinh);
                    }
                    if(new_svien.thangSinh!=0){
                        exchangeSV.thangSinh=new_svien.thangSinh;
                        printf("UPDATING..... %ld: thangSinh => %d\n",MSSV,exchangeSV.thangSinh);
                    }
                    if(new_svien.nam!=0){
                        exchangeSV.nam=new_svien.nam;
                        printf("UPDATING..... %ld: nam => %d\n",MSSV,exchangeSV.nam);
                    }
                    if(IsValidDay(exchangeSV.ngaySinh,exchangeSV.thangSinh,exchangeSV.nam)==0){
                        status = ChangeStruct_To_SV_bin(position,exchangeSV);
                        if(status!=-1){
                            // printf("RESULT!!:\n");
                            // Print_SV_bin();
                            printf("UPDATE \"%ld\" SUCCESSFULLY!!\n",MSSV);
                        }else{
                            printf("UNFORTUNATELY, UPDATE \"%ld\" UNSUCCESSFULLY!!\n", MSSV);
                        }
                    }else{
                        printf("UPDATE FAIL!! THE INFORMATION_DAY INCORRECT!!\n");
                    }
                    
                }else{
                    printf("THIS STUDENT CAN'T BE UPDATED CAUSE ITS EXISTENCE!! PLEASE CHECK AGAIN\n");
                }

            }else{
                //printf("THIS STUDENT: %ld DOESN'T EXIST!!\n",MSSV);
                printf("UPDATE FAIL!!\n");
            }
        }
        return status;
    }



#endif