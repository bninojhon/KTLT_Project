/**         
 * 
 *         < Tạo từng thực thể riêng biệt để dễ dàng sửa chữa nếu có lỗi xảy ra + code gọn gàng >
 * 
 *      Thực thể: Học phần 
 *      Với các chức năng tương ứng gắn với nó, 
 *          Các mô tả chức năng sẽ được viết ở từng hàm
 *          Tổng quát chúng ta có:
 *      1. Struct Học phần -  chứa các thuộc tính 
 *                              "Mã học phần - maHP - kiểu char[8] - quy định length = 6 (- VD "MI1234") "
 *                              "Tên học phần - tenHP - kiểu char[22]" 
 *                              "Số tín chỉ - tin - kiểu int"
 *          ** CHỨC NĂNG PHỤ: 
 *                      + in danh sách học phần hiện có 
 *                      + in một học phần ra ngoài console 
 *                      + tìm một học phần theo mã học phần 
 *      2. Kiểm tra sự tồn tại của học phần trong file HP.bin (IN: tên học phần / Mã học phần, OUT: chỉ số thứ tự học phần trong file)
 *      3. Ghi file HP.bin = Bổ sung học phần (IN: học phần với đầy đủ thông tin (struct HocPhan)) 
 *      4. Xóa 1 học phần (IN: tên học phần/mã học phần)
 *      TEST:  Cập nhật file HP.bin 
 *              + Bổ sung học phần 
 *              + Xóa học phần 
 *              + Cập nhật dữ liệu (vd thay đổi mã học phần, thay đổi tên học phần, thay đổi số tín chỉ)
 *      
 *                      
**/
#ifndef HP_H
    #define HP_H
    #include <stdio.h>
    #include <string.h>
    #define fileHP "D:\\Project_KTLT_C\\fileBin\\HP.bin"
    #define temp_fileHP "D:\\Project_KTLT_C\\fileBin\\temp_HP.bin"

    /**     struct Học phần      **/
    struct HocPhan{
        char maHP[8];           
        char tenHP[22];
        int tin;  
    };
    typedef struct HocPhan HP;         
    
    /*****       PROTOTYPE FOR HOCPHAN      *****/

    //  Chức năng chính: Bổ sung/thêm một học phần vào file HP.bin

        void WriteHP_ToBIN (HP hphan); 

    //  Chức năng chính: Xóa một học phần     

        int Delete_HP(char infor[]);  

    //  Chức năng chính: Cập nhật dữ liệu cho học phần  

        int Update_HP(char infor[], HP new_hphan);

    ///////////////////////////////////////////////////////////////////////////////////////////////////


    //  Chức năng phụ: kiểm tra sự tồn tại của HOC PHAN -> vị trí trong file

        int CheckExist_HP_toPosition(char infor[]);  

    //Chức năng phụ: In danh sách môn học đã có, 
        //phụ cho Print_HP_bin();
        void PrintHeaderFor_HP();   
        void Print_HP_bin();  

    //Chức năng phụ: In thông tin 1 HP sẵn có      
           
        void PrintHP(HP hphan, int position); 

    //Chức năng phụ: Tìm học phần trong file     

        HP FindHP(int position);  //// có thông báo kiểm tra
        HP GetHP_withNoCheck(char maHP[]);

    //Chức năng phụ: Thay đổi 1 Học phần trong file

        int ChangeStruct_To_HP_bin(int position,HP new_hpan); 
        int IsBlank_HP(HP hphan);

    /*****       END PROTOTYPE              *****/

    /////////---------------------------CODING----------------------------------/////////////
 
    int IsBlank_HP(HP hphan){
        if((strcmp(hphan.maHP,"")==0) &&(strcmp(hphan.tenHP,"")==0) && hphan.tin==-1){
            return 0;
        }else{
            return -1;
        }
    }


    void PrintHeaderFor_HP(){
        printf("\t\t\t+-----+----------------+-----------------------+----------+\n");
        printf("\t\t\t|%4s |%14s  |%18s     |%10s|\n","STT","Ma hoc phan","Ten hoc phan","So tin chi");
        printf("\t\t\t+-----+----------------+-----------------------+----------+\n");
    }


    /**     Chức năng phụ : in danh sách học phần hiện có       **/
    void Print_HP_bin(){
        HP tempHp;
        int sizeOfFile = GetSizeOf_bin(fileHP);
        int count=0;
        FILE *hpBin;

        printf("\n");
        printf("\t\t\t+---------------------------------------------------------+\n");
        printf("\t\t\t|\t\t%s\t\t  |\n","DANH SACH CAC HOC PHAN HIEN CO");
        PrintHeaderFor_HP();
        hpBin=fopen(fileHP,"rb");
        if(hpBin!=NULL){
            while(ftell(hpBin)<sizeOfFile){             
                fread(&tempHp, sizeof(HP),1,hpBin);
                printf("\t\t\t|%3d  |%12s    |%20s   |%5d     |\n",++count,tempHp.maHP,tempHp.tenHP,tempHp.tin);
                printf("\t\t\t+-----+----------------+-----------------------+----------+\n");
            }
        }else{
            printf("CANNOT OPEN FILE HP.bin\n");
        }
        fclose(hpBin);
        
    }


    /**     Chức năng phụ: in học phần ra ngoài console|| IN: Học phần nào đó**/
    void PrintHP(HP hphan, int position){
        if(position!=-1){
            PrintHeaderFor_HP();
            printf("\t\t\t|%3d  |%12s    |%20s   |%5d     |\n",position,hphan.maHP,hphan.tenHP,hphan.tin);
            printf("\t\t\t+-----+----------------+-----------------------+----------+\n");
        }else{
            printf("NOT FOUND SUBJECT!!\n");
        }
        
    }

    /** ----------------------------------------------------------------------------------------------------------
     * FUNCTION:(Chức năng phụ:) Thay thế Học phần trên file
     * IN: vị trí học phần nằm ở file,
     *     học phần sẽ thay thế ở vị trí đó (nếu học phấn rỗng thì sẽ xóa học phần tại vị trí đó)
     * OUT: thông số trạng thái
     * - Nếu vị trí không tồn tại (<=-1) thì sẽ không tiến hành mà in thông báo file không có sự thay đổi gì
     *   Ngược lại
     *      Tiến hành duyệt file, 
     *              copy nội dung file từ đầu đến vị trí ta cần thay đổi sang file temp
     *              Đến vị trí cần xét, thực hiện đánh giá Học phần đầu vào
     *              Nếu: Học phần đầu vào là 
     *                  rỗng => bỏ qua dòng đó và nhảy sang phần tử tiếp theo trong file
     *                          tiếp tục copy đến hết file
     *                  Không rỗng => thực hiện viết Học phần vào file mới
     *                                sau đó tiếp tục copy file cũ đến hết
     * - Sau khi đã copy xong, tiến hành xóa file cũ + đổi tên file temp thành file HP.bin
     *  -----------------------------------------------------------------------------------------------------------
    **/
    int ChangeStruct_To_HP_bin(int position,HP new_hpan){
        FILE *hpBin, *temp_hpBin;
        HP exchangeHP;
        int sizeOfFile = GetSizeOf_bin(fileHP);
        int indexByte=0;

        if(position!=-1){
            hpBin = fopen(fileHP,"rb");
            if(hpBin!=NULL){
                temp_hpBin = fopen(temp_fileHP,"wb");
                if(temp_hpBin!=NULL){
                    while(indexByte<sizeOfFile){
                        if(indexByte!=(position-1)*sizeof(HP)){
                            fread(&exchangeHP,sizeof(HP),1,hpBin);
                            fwrite((char*)&exchangeHP,sizeof(HP),1,temp_hpBin);
                        }else{
                            if(strcmp(new_hpan.maHP,"")!=0){
                                fwrite((char*)&new_hpan,sizeof(HP),1,temp_hpBin);
                            }
                            fseek(hpBin,sizeof(HP),SEEK_CUR);
                        }
                        indexByte=ftell(hpBin);
                    }
                }else{
                    printf("CANNOT OPEN FILE temp_HP.bin\n");
                }
                fclose(temp_hpBin);
            }else{
                printf("CANNOT OPEN FILE HP.bin\n");
            }
            fclose(hpBin);

        }else{
            printf("UNVALID POSITION, NOTHING CHANGES!!\n");
        }
        if(indexByte!=0){
            if(remove(fileHP)==0){
                rename(temp_fileHP,fileHP);
                return 0;
            }else{
                printf("UPDATE FAIL!!\n");
            }             /// trong quá trình xóa file, không được mở 2 file lên   
        }
        return -1;
    }

    /** ----------------------------------------------------------------------------------------------------------    
     * FUNCTION: (phụ) Kiểm tra sự tồn tại của học phần theo thông tin: 
     * IN: Mã học phần hoặc Tên học phần,
     * OUT: thứ tự của môn học trong File hoặc thông báo chưa tồn tại
     *  - Tiến hành duyệt file, nếu file không mở được thì thông báo ra màn hình và không tiến hành các bước tiếp
     *  - Nếu thông tin về mã học phần/tên học phần trùng với yêu cầu
     *          In ra thông báo tồn tại và trả về vị trí của môn học trong file
     *    Nếu không thì trả về -1 và thông báo không tồn tại
     * -----------------------------------------------------------------------------------------------------------
    **/ 
    int CheckExist_HP_toPosition(char infor[]){
        HP tempHp={"","",0};
        int sizeOfFile = GetSizeOf_bin(fileHP);
        int count=0,result=0;
        FILE *hpBin;

        hpBin=fopen(fileHP,"rb");
        if(hpBin!=NULL){
            while(ftell(hpBin)<sizeOfFile){
                count++;
                fread(&tempHp, sizeof(HP),1,hpBin);
                if(strcmp(tempHp.maHP,infor)==0 || strcmp(tempHp.tenHP,infor)==0){
                    printf("THIS SUBJECT: %s EXISTED!!!!\n",infor);
                    result=count;
                    //PrintHP(tempHp);
                    //printf("PLEASE READ \"HP.bin\" AGAIN BEFORE INSERTING ANOTHER!!\n");
                    break;
                }
            }
            if((ftell(hpBin)==sizeOfFile && result==0) || count==0){
                printf("THIS SUBJECT: %s DOESN'T EXIST!!\n",infor);
                result=-1;
            }
        }else{
            printf("CANNOT OPEN FILE HP.bin\n");
            result=-1;
        }
        fclose(hpBin);
        return result;
    }

    /** ----------------------------------------------------------------------------------------------------------------
     *    FUNCTION:(phụ) Tìm kiếm học phần  
     *    IN: mảng xâu kí tự chứa nội dung là Mã học phần/tên mã học phần
     *    OUT: Một struct Học phần
     *    - Tiến hành đọc file BIN, nếu file không mở được tiến hành báo lỗi còn không thì chạy bình thường
     *    - Tiến hành kiểm tra HOCPHAN đã tồn tại chưa
     *    - Nếu : tìm được mã học phần/tên học phần cần tìm 
     *               =>> thông báo tìm thấy, và in ra màn hình vị trí và thông tin HP, trả về học phần
     *      Trái lại:
     *              =>> thông báo không tồn tại, trả về học phần BLANK
     *    
     * ------------------------------------------------------------------------------------------------------------------         
    **/
    HP FindHP(int position){
        HP tempHp={"","",0};
        FILE *hpBin;

        if(position!=-1){
            hpBin=fopen(fileHP,"rb");
            if(hpBin!=NULL){
                fseek(hpBin,(position-1)*sizeof(HP),SEEK_SET);
                fread(&tempHp,sizeof(HP),1,hpBin);
                PrintHP(tempHp,position);
            }else{
                printf("CANNOT OPEN FILE HP.bin\n");
            }
            fclose(hpBin);
        }else{
            printf("THIS OBJECT DOESN'T EXIST!!\n");
        }    
        return tempHp;
    }
    /**
     *  Chức năng phụ: lấy struc HP thông qua MSSV // chỉ dùng khi đảm bảo HP có trong file
    **/
    HP GetHP_withNoCheck(char maHP[]){
        HP hphan={"","",0};
        FILE *hpBin;
        int sizeOfFile = GetSizeOf_bin(fileHP);
        hpBin = fopen(fileHP,"rb");
        if(hpBin!=NULL){
            while(ftell(hpBin)<sizeOfFile){
                fread(&hphan,sizeof(HP),1,hpBin);
                if(strcmp(hphan.maHP,maHP)==0){
                    fclose(hpBin);
                    break;
                }
            }
        }else{
            printf("GetHP_withNoCheck : CANNOT OPEN FILE HP.bin!!\n");
            fclose(hpBin);
        }
        return hphan;
    }


    /** ------------------------------------------------------------------------------    
     *  PROCEDURE:  (chính) Ghi học phần vào file HP.bin
     *  IN: học phần bất kỳ miễn là chưa tồn tại trong file
     *  - Tiến hành kiểm tra HP.bin xem trong file đã tồn tại học phần này hay chưa
     *  - Nếu đã tồn tại: 
     *          => In ra màn hình thông báo học phần đã tồn tại 
     *             và Không thêm vào file, thủ túc kết thúc
     *    Trái lại: 
     *          => Thêm vào file và in thông báo thành công
     * --------------------------------------------------------------------------------
    **/
    void WriteHP_ToBIN (HP hphan){
        FILE *hpBin;
        int position;

        hpBin=fopen(fileHP,"ab");
        if(hpBin!=NULL){
            if(CheckExist_HP_toPosition(hphan.maHP)==-1){      //// nếu tồn tại thì hàm CheckExist_HP_toPosition sẽ in ra màn hình
                fwrite(&hphan,sizeof(HP),1,hpBin);
                printf("INSERT SUCCESSFULLY!!\n");
            }else{
                //printf("THIS SUBJECT: %s EXISTS!!\n",hphan.maHP);
                printf("PLEASE READ \"HP.bin\" AGAIN BEFORE INSERTING ANOTHER!!\n");
            }
        }else{
            printf("CANNOT OPEN FILE HP.bin\n");
        }
        fclose(hpBin);

    }
    /** ----------------------------------------------------------------------------------------------------------------------
     * PROCEDURE: (chính) Xóa một học phần theo thông tin người dùng
     * IN: xâu ký tự chứa thông tin về mã học phần/tên học phần 
     * OUT: 0 nếu xóa thành công, -1 nếu gặp vấn đề trong lúc xóa
     * - Tiến hành kiểm tra sự tồn tại của học phần
     *     -Nếu đã tồn tại, thủ tục kết thúc và báo lỗi
     *     -Nếu không, thì tiếp tục tiến trình và lấy kết quả vị trí học phần từ hàm CheckExist_HP_toPosition(char infor[])
     * - Tiến hành thay thế vị trí đó trong file bởi 1 blank HP 
     * - Nếu xóa thành công sẽ hiển thị thông báo ra màn hình và in kết quả
     * -----------------------------------------------------------------------------------------------------------------------
    **/
    int Delete_HP(char infor[]){
        
        int position = CheckExist_HP_toPosition(infor);
        int status=-1;
        HP blankHP ={"","",0};

        if(position!=-1){
            status = ChangeStruct_To_HP_bin(position,blankHP);
            if(status!=0){
                printf("UNFORTUNATELY, DELETE \"%s\" UNSUCCESSFULLY!!\n", infor);
            }else{
                printf("RESULT: \n");
                Print_HP_bin();
                printf("DELETE \"%s\" SUCCESSFULLY!!\n", infor);
            }
        }else{
            printf("DELETE FAIL!!!\n");
        }
        return status;
    }

    /** --------------------------------------------------------------------------------------------------------------
     * PROCEDURE: (chính) Cập nhật dữ liệu cho học phần 
     * IN: (infor)xâu ký tự về mã học phần/tên học phần
     *     xâu ký tự về mã học phần mới (nếu không thay đổi thì để "")
     *     xâu ký tự về tên học phần mới (nếu không thay đổi thì để "")
     *     số tín chỉ mới(nếu không thay đổi để -1)
     * OUT:0 nếu update thành công, -1 nếu gặp vấn đề trong quá trình
     * - Từ thông tin đầu vào, tiến hành kiểm tra trong file xem học phần đã tồn tại hay chưa??
     * - Nếu chưa tồn tại
     *        Ngừng hàm, báo lỗi chưa tồn tại ra màn hình
     *   Nếu đã tồn tại 
     *         Tiếp tục tiến hành các bước sau
     * - Kiểm tra liệu NDUng đầu vào liệu có làm thay đổi HP không??
     *      Nếu có: Tiếp tục thực hiện
     *      Nếu không: trả về thông báo không có sự thay đổi gì
     * - Thực hiện thay đổi tùy ý(lựa chọn thay đổi thông tin đến khi phù hợp)
     * - Sau khi thực hiện thay đổi, 
     *      tiến hành thay thế học phần (thay trực tiếp tại file, tại dòng của học phần cũ)
     *      thông báo thay đổi thành công, và in ra màn hình danh sách hiện tại
     *      (Thông báo những thông tin đã được thay đổi)
     * ----------------------------------------------------------------------------------------------------------------
    **/
    int Update_HP(char infor[], HP new_hphan){
        FILE *hpBin, *temp_hpBin;
        HP exchangeHP = {"","",-2};
        int status=-1;
        int position = CheckExist_HP_toPosition(infor);
        int positionName, positionId;
        char old_maHP[8], old_tenHP[22];
        int old_tin;

        if(position!=-1){
            exchangeHP = FindHP(position);
            strcpy(old_maHP,exchangeHP.maHP);
            strcpy(old_tenHP,exchangeHP.tenHP);
            old_tin = exchangeHP.tin;
            if(strcmp(new_hphan.maHP,"")!=0){
                strcpy(exchangeHP.maHP,new_hphan.maHP);
            }
            if(strcmp(new_hphan.tenHP,"")!=0){
                strcpy(exchangeHP.tenHP,new_hphan.tenHP);
            }
            if(new_hphan.tin!=-1){
                if(new_hphan.tin<-1){
                    printf("ERROR!! Value for \"tin\" can't be negative!!\n");
                    printf("UPDATE FAIL!!\n");
                }else{
                    exchangeHP.tin=new_hphan.tin;
                }
            }
            if(strcmp(old_maHP,exchangeHP.maHP)!=0 || strcmp(old_tenHP,exchangeHP.tenHP)!=0 || old_tin!=exchangeHP.tin){
                positionName = CheckExist_HP_toPosition(exchangeHP.tenHP);
                positionId = CheckExist_HP_toPosition(exchangeHP.maHP);
                if((positionId==position && positionName==-1)||(positionId==-1 && positionName==position)||(positionId==position && positionName==position)||(positionId==-1 && positionName ==-1)){
                    /*
                        Chỉ thay đổi khi
                            - Mã học phần đã tồn tại thì phải đúng vị trí ban đầu
                                đồng thời thông tin về Tên hp phải chưa tồn tại
                            - Tên học phần đã tồn tại thì phải đúng vị trí ban đầu
                                đồng thời mã học phần phải chưa tồn tại
                            - Nếu cả hai đã tồn tại thì cả hai phải nằm đúng vị trí cần update
                        nếu không thì chứng tỏ bị trùng lặp nếu update
                    */
                    status = ChangeStruct_To_HP_bin(position,exchangeHP);
                    if(status!=-1){
                        printf("RESULT:\n");
                        Print_HP_bin();
                        if(strcmp(old_tenHP,exchangeHP.tenHP)!=0 ){
                            printf("UPDATE %s to %s SUCCESSFULLY!!\n",infor,exchangeHP.tenHP);
                        }
                        if(strcmp(old_maHP,exchangeHP.maHP)!=0){
                            printf("UPDATE %s to %s SUCCESSFULLY!!\n",infor,exchangeHP.maHP);
                        }
                        if(old_tin!=exchangeHP.tin){
                            printf("UPDATE %s: %d tin to %d tin  SUCCESSFULLY!!\n",infor,old_tin,exchangeHP.tin);
                        }
                        
                    }else{
                        printf("UNFORTUNATELY, UPDATE \"%s\" UNSUCCESSFULLY!!\n", infor);
                    }
                }else{
                    printf("%s EXISTED, READ HP.bin CAREFULLY\n",infor);
                }
            }else{
                printf("NOTHING CHANGE!!!\n");
            }
        }else{
            //printf("THIS SUBJECT: %s DOESN'T EXIST!!\n",infor);
            printf("UPDATE FAIL!!\n");
        }
        return status;
        
    }

#endif