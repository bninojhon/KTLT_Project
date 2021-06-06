/**
 * 
 *         < Tạo từng thực thể riêng biệt để dễ dàng sửa chữa nếu có lỗi xảy ra + code gọn gàng >
 * 
 *      Thực thể: Điểm thi 
 *      Với các chức năng tương ứng gắn với nó, 
 *          Các mô tả chức năng sẽ được viết ở từng hàm
 *          Tổng quát chúng ta có:
 *      1. Struct Điểm thi -  chứa các thuộc tính 
 *                              MSSV - kiểu long 
 *                              maHP - kiểu xâu ký tự
 *                              điểm thi - kiểu float - lấy 1 chữ số sau dấu phẩy, được làm tròn lên 0.5
 *          ** CHỨC NĂNG PHỤ: 
 *                      + in danh sách
 *                                  * Bảng điểm của 1 sinh viên
 *                                  * Bảng điểm của 1 môn học
 *                                   
 *                      + in bảng điểm của  1 sinh viên và  1 môn học
 *      2. Ghi file DIEMTHI.bin = Viết thêm thành tích (IN: Struct DiemThi)
 *      3. Xóa thành tích
 *      TEST:  Cập nhật file DIEMTHI.bin 
 *              + Bổ sung học phần 
 *              + Xóa học phần 
 *              + Cập nhật dữ liệu (vd thay đổi mã học phần, thay đổi tên học phần, thay đổi số tín chỉ)
 *      
 *                      
**/
#ifndef DIEMTHI_H
    #define DIEMTHI_H
    #ifndef SV_H             
        #include <SV.h>
    #endif
    #ifndef HP_H
        #include <HP.h>
    #endif

    #include <string.h>
    #include <stdio.h>
    #define fileDIEMTHI "D:\\Project_KTLT_C\\fileBin\\DIEMTHI.bin"
    #define temp_fileDIEMTHI "D:\\Project_KTLT_C\\fileBin\\temp_DIEMTHI.bin"

    enum SELECTION {LOWER, LOWER_EQ, EQUAL, GREAT_EQ, GREAT, ALL};
    typedef enum SELECTION SELECT; 

    struct DiemThi {
        long MSSV;          
        char maHP[8];
        float diem;
    };
    typedef struct DiemThi DT;

    //      PROTOTYPE FOR DiemThi
        //Chức năng chính:    Kiểm tra sự tồn tại của struct DIEMTHI trong file DIEMTHI.bin 

        int CheckExist_DT_toPosition(long MSSV, char maHP[]); 

        // Chức năng chính: Viết hay thêm mới 1 bản ghi

        void WriteDT_toBIN(DT diemHPSV);

        //  Chức năng chính: Xóa một bản ghi     

        int Delete_DT(long MSSV, char maHP[]);  

        //  Chức năng chính: Cập nhật dữ liệu cho diem thi  

        int Update_DT(long MSSV, char maHP[], DT new_dthi);

        /////       MỤC TIÊU CHO CÂU 4      ////
        //Chức năng chính:   In bảng điểm của 1 sinh viên

        void SelectDTBin_HP_BySV(long MSSV, float diem, SELECT choice);
        void PrintHeaderForDT_HP_SV(long MSSV);
        void PrintHP_bySV_with_diemHP(int position,HP hphan, float diem);

        ////        MỤC TIÊU CHO CÂU 5      ///
        //Chức năng phụ:   In bảng điểm của 1 môn học

        void SelectDTBin_SV_byHP(char maHP[], float diem, SELECT choice);
        void PrintHeaderForDT_SV_HP(HP hphan);
        void PrintSV_byHP_with_diemHP(int position,SV svien, float diem);

        ////////////////////////////////////////////////////////////////////////////////////////////

        // Chức năng phụ cho selection
        int FolowSelect(float diemDT, SELECT choice, float diem);

        // Chức năng chính/phụ:   Kiểm tra sự tồn tại của cả sinh viên và học phần trong file bin 
    
        int IsValid_SV_HP(long MSSV, char maHP[]);
        
        // Chức năng phụ    Làm tròn điểm học phần

        float Round_diemHP(float diem);

        // Chức năng phụ kiểm tra điểm vào có hợp lệ 

        int IsValid_diemHP(float diem);

        // Chức năng phụ kiểm tra struct diemthi có phải là 1 blank không

        int IsBlank_DT(DT dthi);


        // Chức năng phụ:   Thay đổi dữ liệu bản ghi DIEMTHI
        int ChangeStruct_To_DT_bin(int position,DT new_dthi);
        

        //Chức năng phụ:    Tìm một struct SV theo (MSSV và mã học phấn)

        DT FindDT(int position);
        DT GetDT_withNoCheck(long MSSV, char maHP[]);


        //Chức năng phụ: In điểm của sinh viên và môn học đó
        void PrintDT(DT dthi, int position);

        // Chức năng phụ: Đồng bộ lại toàn bộ file DIEMTHI

        void Sync_DT_binForSV(long del_MSSV);
        void Sync_DT_binForHP(char del_maHP[]);

    /////////////////// END PROTOTYPE //////////////////////////////
    /**
     * 
     * 
     * 
     * 
     * 
     * 
     * 
    **/
    //////////////////// CODING /////////////////////////////////////
    /**
     *       Chức năng: lấy giá trị cho DT khi đã chắc chắn biết sự tồn tại 
     *      
    **/
    DT GetDT_withNoCheck(long MSSV, char maHP[]){
        FILE * dtBin;
        DT new_DT;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        dtBin = fopen(fileDIEMTHI,"rb");
        if(dtBin!=NULL){
            while(ftell(dtBin)<sizeOfFile){
                fread(&new_DT,sizeof(DT),1,dtBin);
                if((new_DT.MSSV==MSSV) && (strcmp(new_DT.maHP,maHP)==0)){
                    break;
                }
            }
        }else{
            printf("\nGetDT_withNoCheck CANNOT OPEN FILE DIEMTHI.h\n");
        }
        fclose(dtBin);
        return new_DT;
    }

    /** --------------------------------------------------------------------------------------------------
     * FUNCTION: Kiểm tra diemthi có phải là 1 blank không
     * IN: struct diemthi
     * OUT: 0 nếu đúng, -1 nếu sai
     * ---------------------------------------------------------------------------------------------------
    **/
    int IsBlank_DT(DT dthi){
        if((dthi.MSSV==0) && (strcmp(dthi.maHP,"")==0) && (dthi.diem==-1)){
            return 0;
        }else{
            return -1;
        }
    }
    /** -------------------------------------------------------------------------------------------------------------------
     * FUNCTION: (Chức năng chính:) Kiểm tra sự hơp lệ của MSSV và maHP = Kiểm tra sự tồn tại của SinhVien và HocPhan
     * IN: Mã số sinh viên và mã học phần cần nhập điểm
     * OUT: trả về 0 nếu cả hai đều tồn tại, 
     *            -1 nếu 1 trong hai không tồn tại,
     * 
     * - Sử dụng các hàm CheckExist với MSSV và maHP để nhận lấy vị trí của lần lượt Sinh vien, HPhan
     * - Xét vị trị của SinhVien thông qua MSSV,
     *       nếu không tồn tại thì thông báo không tồn tại sinh viên,  hàm return về -1
     *       nếu tồn tại, tiếp tục xét
     * - Xét vị trí của HocPhan thông qua maHP 
     *       nếu không tồn tại thì thông báo không tồn tại học phần, hàm return về -1
     *       nếu tồn tại, 
     *              Chứng tỏ cả Sinh viên và Học Phần đều tồn tại
     *              return về 0
     * ---------------------------------------------------------------------------------------------------------------------
    **/
    int IsValid_SV_HP (long MSSV, char maHP[]){
        int count = 0;
        int positionOfSV = CheckExist_SV_toPosition(MSSV);   // kiểm tra sinh vien đã tồn tại chưa, và lấy vị trí sinh viên nếu đã tồn tại
        int positionOfHP = CheckExist_HP_toPosition(maHP);   // kiểm tra học phần đã tồn tại chưa, và lấy vị trí học phần nếu đã tốn tại   
        if(positionOfSV==-1){                                           // Điều kiện chạy: sinh viên không tồn tại ở file SV.bin
            count ++;
            printf("!!! ERROR: STUDENT NOT FOUND!!\n");
            printf("PLEASE READ \"SV.bin\" to check out!\n");
        }
        if(positionOfHP==-1){                                       // Điều kiện chạy: học phần không tồn tại ở file HP.bin
            count++;
            printf("!!! ERROR: SUBJECT NOT FOUND!!\n");
            printf("PLEASE READ \"HP.bin\" to check out!\n");
        }
        if(count!=0){
            return -1;
        }else{
            return 0;
        }
    }
    /** ------------------------------------------------------------------------------------------------------
     * FUNCTION: (phụ) Kiểm tra sự hợp lệ của điểm nhập đầu vào
     * IN: điểm nhập
     * OUT: 0 nếu điểm hợp lệ, -1 nếu không hợp lệ
     * <<<<<    Điểm hợp lệ là điểm nằm trong [0,10];   >>>>>
     * -------------------------------------------------------------------------------------------------------
    **/
    int IsValid_diemHP(float diem){
        if(diem<0 || diem >10){
            printf("UNVALID VALUE: NOT IN 0<= DIEM <=10 \n");
            return -1;
        }else{
            return 0;
        }
    }

    /** ------------------------------------------------------------------------------------------------------
     * FUNCTION: (chính)Chức năng làm tròn điểm học phần
     * IN: điểm nhập
     * OUT: điểm được làm tròn
     * - xuống 0 nếu nhỏ hơn 0.5
     * - xuống 0.5 nếu nhỏ hơn 0.75 và lớn hơn hoặc bằng 0.5
     * - lên 1 nếu lớn hơn hoặc bằng 0.75
     * ---------------------------------------------------------------------------------------------------------
    **/
    float Round_diemHP(float diem){
        int integer = diem;
        float decimalPart = diem - integer;
        if(decimalPart<0.5){
            diem = integer;
        }else if (decimalPart<0.75){
            diem = integer + 0.5;
        }else{
            diem = integer + 1;
        }
        return diem;
    }

    // Chức năng phụ cho selection
    int FolowSelect(float diemDT, SELECT choice, float diem){
        if(((choice == LOWER) && (diemDT<diem))
            ||((choice == LOWER_EQ) && (diemDT <= diem))
            ||((choice == EQUAL) && (diemDT == diem))
            ||((choice == GREAT_EQ) && (diemDT >= diem))
            ||((choice == GREAT) && (diemDT > diem)) ){
                return 0;
        }else{
            return -1;
        }
    }

    /////// Chức năng phụ cho SelectDTBin_HP_bySV(MSSV)
    void PrintHP_bySV_with_diemHP(int position,HP hphan, float diem){
        printf("\t\t|%3d  |%12s    |%20s   |%5d     |   %4.1f    |\n",position,hphan.maHP,hphan.tenHP,hphan.tin,diem);
        printf("\t\t+-----+----------------+-----------------------+----------+-----------+\n");

    }
    /////// Chức năng phụ cho SelectDTBin_HP_bySV(MSSV)
    void PrintHeaderForDT_HP_SV(long MSSV){
        printf("\n");
        printf("\t\t+---------------------------------------------------------------------+\n");
        printf("\t\t|\t\t\t%2s: %ld\t\t      |\n","BANG DIEM SVIEN",MSSV);
        printf("\t\t+-----+----------------+-----------------------+----------+-----------+\n"); 
        printf("\t\t|%4s |%14s  |%18s     |%10s|%9s  |\n","STT","Ma hoc phan","Ten hoc phan","So tin chi","DiemThi");
        printf("\t\t+-----+----------------+-----------------------+----------+-----------+\n");  
    }
    /** ---------------------------------------------------------------------------------------------------------
     *  PROCEDURE:(Chức năng phụ)   In điểm học phần của 1 sinh viên
     *  --------------------------------------------------------------------------------------------------------
    **/
    void SelectDTBin_HP_BySV(long MSSV, float diem, SELECT choice){
        SV svien = {0,"","","","",0,0,0};                   /// Một Sinh vien rỗng
        HP hphan = {"","",0};                               /// Học phần rỗng
        DT searchDt ;                                      
        FILE *dtBin;                                        /// con trỏ file duyệt DIEMTHI.bin
        int positionOfSV = CheckExist_SV_toPosition(MSSV);  /// lấy vị trí Sinh viên và in thông tin nếu tồn tại
        /* Kiểm tra sự tồn tại của sinh viên và lấy thông tin vị trí của sinh viên trong file */
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);  
        int count=0;
        if(positionOfSV!=-1){
            svien = FindSV(positionOfSV);               //// tìm thông tin sinh viên để in ra màn hình
            PrintHeaderForDT_HP_SV(MSSV);
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                while(ftell(dtBin)<sizeOfFile){
                    fread(&searchDt,sizeof(DT),1,dtBin);
                    if(searchDt.MSSV==MSSV){
                        if ((FolowSelect(searchDt.diem,choice,diem)==0) || (choice == ALL)){
                            count++;
                            hphan = GetHP_withNoCheck(searchDt.maHP);
                            PrintHP_bySV_with_diemHP(count,hphan,searchDt.diem);
                        }
                    }
                }
            }else{
                printf("SelectDTBin_HP_BySV: CANNOT OPEN FILE DIEMTHI.bin\n");
            }
            fclose(dtBin);
        }else{
            printf("CAN'T PRINT\n");
        }

    }
    //Chức năng phụ: In điểm của sinh viên và môn học đó
        void PrintDT(DT dthi, int position){
            HP hphan;
            if(position>-1){
                PrintHeaderForDT_HP_SV(dthi.MSSV);
                hphan = GetHP_withNoCheck(dthi.maHP);
                PrintHP_bySV_with_diemHP(position,hphan,dthi.diem);
            }else{
                printf("NOT FOUND RECORD!\n");
            }
        }

    /// Chức năng phụ cho Print_DT_bin
    void PrintHeaderForDT_SV_HP(HP hphan){
        printf("\n");
        printf("+----------------------------------------------------------------------------------+\n");
        printf("|\t    %2s: %20s - %s - %d tin chi\t   |\n","BANG DIEM HOC PHAN MON: ",hphan.tenHP,hphan.maHP,hphan.tin);
        printf("+-----+----------------+------------+------------------+-----------+---------------+\n");
        printf("|%5s|%16s|%30s             |%15s|\n"," "," ","Ten Sinh vien"," "," ");
        printf("|%4s |%12s    |------------+------------------+-----------|%14s |\n","STT","Ma so SV","Diem Hoc Phan");
        printf("|%5s|%16s|%7s     |%10s        |%9s  |%15s|\n"," "," ","Ho","Dem","Ten"," ");
        printf("+-----+----------------+------------+------------------+-----------+---------------+\n");
    }
    void PrintSV_byHP_with_diemHP(int position,SV svien, float diem){
        printf("|%3d  |%12d    |%10s  |%17s |%9s  |   %6.1f      |\n"
        ,position,svien.MSSV, svien.ho, svien.dem, svien.ten
        , diem);
        printf("+-----+----------------+------------+------------------+-----------+---------------+\n");
    }
    /** -------------------------------------------------------------------------
     * PROCEDURE: in bảng điểm của 1 học phần 
     * --------------------------------------------------------------------------
    **/
    void SelectDTBin_SV_byHP(char maHP[], float limit, SELECT choice){
        SV svien = {0,"","","","",0,0,0};                   /// Một Sinh vien rỗng
        HP hphan = {"","",0};                               /// Học phần rỗng
        DT searchDt ;
        FILE *dtBin;                                        /// con trỏ file duyệt DIEMTHI.bin
        int positionOfHP = CheckExist_HP_toPosition(maHP);  /// lấy vị trí Học Phần và in thông tin nếu tồn tại
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);  
        int count=0;
        if(positionOfHP!=-1){
            hphan = FindHP(positionOfHP);               //// tìm thông tin sinh viên 
            PrintHeaderForDT_SV_HP(hphan);
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                while(ftell(dtBin)<sizeOfFile){
                    fread(&searchDt,sizeof(DT),1,dtBin);
                    if(strcmp(searchDt.maHP,maHP)==0){
                        if (FolowSelect(searchDt.diem,choice,limit)==0 || (choice == ALL)){
                            count++;
                            svien = GetSV_withNoCheck(searchDt.MSSV);
                            PrintSV_byHP_with_diemHP(count,svien,searchDt.diem);    
                        }
                    }
                }
            }else{
                printf("SelectDTBin_SV_ByHP: CANNOT OPEN FILE DIEMTHI.bin\n");
            }
            fclose(dtBin);
        }else{
            printf("CAN'T PRINT\n");
        }
    }

    /** ------------------------------------------------------------------------------------------
     * FUNCTION:(Chức năng phụ:) Kiểm tra sự tồn tại của bản ghi điểm của sinh viên
     * IN: Mã số sinh viên, mã học phần và biến status trạng thái
     * OUT: Vị trí của bản ghi nếu tồn tại
     *      Hoặc -1 để thông báo bản ghi chưa tồn tại và có thể ghi vào
     *      Hoặc -2 để thông báo sinh viên/học phần chưa tồn tại
     * -------------------------------------------------------------------------------------------- 
    **/
    int CheckExist_DT_toPosition(long MSSV, char maHP[]){
        FILE *dtBin;
        DT searchDT;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        int count=0, result=0;
        int status = IsValid_SV_HP(MSSV,maHP);

        if(status==0){
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                while(ftell(dtBin)<sizeOfFile){
                    count++;
                    fread(&searchDT,sizeof(DT),1,dtBin);
                    if(searchDT.MSSV==MSSV && (strcmp(searchDT.maHP,maHP)==0)){
                        printf("THIS RECORD: %ld, %s EXISTED!!\n",MSSV,maHP);
                        result = count;
                        break;
                    }
                }
                if((ftell(dtBin)==sizeOfFile && result==0) || count==0){    /// Nếu duyệt hết file mà không có kết quả
                    printf("THIS RECORD: %ld - %s DOESN'T EXISTS!!\n",MSSV,maHP);     /// Hoặc file rỗng
                    result=-1;                                              /// Kết quả là không tồn tại
                }
            }else{
                printf("CheckExist_DT_toPosition: \n");
                printf("CANNOT OPEN FILE DIEMTHI.bin\n");
                printf("CHECK YOUR FILE STREAM AGAIN!!\n");
                result=-1;
            }
            fclose(dtBin);
            return result;
        }else{
            result = -2;
        }
        return result;
    }
    /** ----------------------------------------------------------------------------------------------------------------
     * FUNCTION:  (Chức năng phụ) Thay thế DiemThi trên file
     * IN: vị trí diemthi nằm ở file,
     *     diem thi mới sẽ thay thế ở vị trí đó (nếu diemthi mới rỗng(isBlank) thì sẽ xóa diemthi tại vị trí đó)
     * OUT: 0 nếu quá trình thay đổi thành công, -1 nếu thất bại
     * 
     * - Nếu vị trí không tồn tại (<=-1) 
     *      thì sẽ không tiến hành mà in thông báo file không có sự thay đổi gì
     *      return -1
     *   Ngược lại
     *      Tiến hành duyệt file, 
     *              copy nội dung file từ đầu đến vị trí ta cần thay đổi sang file temp
     *              Đến vị trí cần xét, thực hiện đánh giá diemthi đầu vào
     *              Nếu: diemthi đầu vào là 
     *                  rỗng => bỏ qua dòng đó và nhảy sang phần tử tiếp theo trong file
     *                          tiếp tục copy đến hết file 
     *                  Không rỗng => thực hiện viết sinh viên vào file mới
     *                                sau đó tiếp tục copy file cũ đến hết
     *      Nếu file không mở được => return -1;
     * - Sau khi đã copy xong, tiến hành xóa file cũ + đổi tên file temp thành file DIEMTHI.bin return 0
     * -------------------------------------------------------------------------------------------------------------------
    **/
    int ChangeStruct_To_DT_bin(int position,DT new_dthi){
        FILE *dtBin, *temp_dtBin;
        DT exchangeDT;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        int indexByte=0;

        if(position>-1){
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                temp_dtBin = fopen(temp_fileDIEMTHI,"wb");
                if(temp_dtBin!=NULL){
                    while(indexByte<sizeOfFile){
                        if(indexByte!=(position-1)*sizeof(DT)){
                            fread(&exchangeDT,sizeof(DT),1,dtBin);
                            fwrite((char*)&exchangeDT,sizeof(DT),1,temp_dtBin);
                        }else{
                            if(IsBlank_DT(new_dthi)!=0){
                                fwrite((char*)&new_dthi,sizeof(DT),1,temp_dtBin);
                            }
                            fseek(dtBin,sizeof(DT),SEEK_CUR);
                        }
                        indexByte=ftell(dtBin);
                    }
                }else{
                    printf("CANNOT OPEN FILE temp_DT.bin\n");
                }
                fclose(temp_dtBin);
            }else{
                printf("CANNOT OPEN FILE DT.bin\n");
            }
            fclose(dtBin);

        }else{
            printf("UNVALID POSITION, NOTHING CHANGES!!\n");
        }
        if(indexByte!=0){
            if(remove(fileDIEMTHI)==0){
                rename(temp_fileDIEMTHI,fileDIEMTHI);
                return 0;
            }else{
                printf("UPDATE FAIL!!\n");
            }             /// trong quá trình xóa file, không được mở 2 file lên   
        }
        return -1;
    }
    /** ----------------------------------------------------------------------------------------------------------
     * PROCEDURE:(Chức năng chính:) Viết điểm thi vào file DIEMTHI.bin
     * IN: struct DiemThi
     * 
     * - Kiểm tra sự tồn tại của bản ghi điểm của Sinh viên về môn nào đó
     * - Nếu  
     *        Đã tồn tại, thông báo không được ghi đè, thủ tục kết thúc
     *        Sinh viên/Học phần chưa có trong file SV.bin/HP.bin
     *              Thông báo Không thể ghi record
     *        Chưa tồn tại, tiếp tục tiến hành quá trình ghi vào file
     *              Ghi thành công, thông báo ra màn hình
     *              Nếu gặp lỗi trong quá trình ghi, in ra thông báo lỗi và dừng thủ tục
     * ---------------------------------------------------------------------------------------------------------
    **/
    void WriteDT_toBIN(DT new_diemHPSV){
        FILE *dtBin;
        int position = CheckExist_DT_toPosition(new_diemHPSV.MSSV,new_diemHPSV.maHP);
        if(position==-1){
            if(IsValid_diemHP(new_diemHPSV.diem)==0){
                printf("WRITING....\n");
                new_diemHPSV.diem = Round_diemHP(new_diemHPSV.diem);
                dtBin = fopen(fileDIEMTHI,"ab");
                if(dtBin!=NULL){
                    fwrite(&new_diemHPSV,sizeof(DT),1,dtBin);
                    printf("INSERT SUCCESSFULLY!!\n");
                }else{ 
                    printf("CANNOT OPEN DIEMTHI.bin\nCHECK YOUR FILE STREAM AGAIN!!\n");
                }    
                fclose(dtBin);
            }else{
                printf("INSERT FAIL!!\n");
            }
        }else if(position<-1){
            printf("CANNOT WRITE RECORD TO FILE DIEMTHI.bin!!\n");
        }else{
            printf("CANNOT OVERWRITE!!!\n");
        }
    }
    // Chức năng phụ: Lấy dữ liệu Dthi từ vị trí trong file
    DT FindDT(int position){
        DT tempDT={0,"",-1};
        FILE *dtBin;

        if(position>-1){
            dtBin=fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                fseek(dtBin,(position-1)*sizeof(DT),SEEK_SET);
                fread(&tempDT,sizeof(DT),1,dtBin);
                PrintDT(tempDT,position);
            }else{
                printf("CANNOT OPEN FILE DT.bin\n");
            }
            fclose(dtBin);
        }else{
            printf("THIS OBJECT DOESN'T EXIST!!\n");
        }    
        return tempDT;
    }
    /**
     * PROCEDURE: Xóa một DiemThi theo thông tin người dùng
     * IN: Cặp sinh viên(MSSV)-Học phần(maHP) cần xóa
     * - Tiến hành kiểm tra sự tồn tại của sinh viên
     *     -Nếu đã tồn tại, thủ tục kết thúc và báo lỗi
     *     -Nếu không, thì tiếp tục tiến trình và lấy kết quả vị trí sinh viên từ hàm CheckExist_DT_toPosition(long MSSV, char maHP[])
     * - Tiến hành thay thế vị trí đó trong file bởi 1 blank SV 
     * - Nếu xóa thành công sẽ hiển thị thông báo ra màn hình và in kết quả
     * 
    **/     
    int Delete_DT(long MSSV, char maHP[]){
        int position = CheckExist_DT_toPosition(MSSV,maHP);
        int status=-1;
        DT blankDT ={0,"",0};

        if(position>-1){
            status = ChangeStruct_To_DT_bin(position,blankDT);
            if(status!=0){
                printf("UNFORTUNATELY, DELETE RECORD UNSUCCESSFULLY!!\n");
            }else{
                printf("RESULT: \n");
                FindSV(position);
                printf("DELETE RECORD SUCCESSFULLY!!\n");
            }
        }else{
            printf("DELETE FAIL!!!\n");
        }
        return status;
    } 
    /** ---------------------------------------------------------------------------------------------------------------
     * PROCEDURE: Cập nhật dữ liệu cho sinh viên 
     * IN: Cặp MSSV - học phần cần thay đổi, một struct Diemthi mới
     * 
     * - Từ thông tin đầu vào, tiến hành kiểm tra xem sinh viên và học phần cần thay đổi có tồn tại không
     * - Nếu chưa tồn tại
     *        Ngừng hàm, báo lỗi chưa tồn tại ra màn hình
     *   Nếu đã tồn tại 
     *         Tiếp tục tiến hành các bước sau
     * - Kiểm tra việc lặp dữ liệu nếu thay đổi?
     *      Nếu có: Ngừng thủ tục và tiến hành báo lỗi
     *      Nếu không: lấy thông tin của struct DiemThi trong file cần thay đổi
     *                 Thực hiện cập nhật struct để chuẩn bị quá trình nạp vào file
     * - Sau khi thực hiện thay đổi, 
     *      tiến hành thay thế DiemThi (thay trực tiếp tại file, tại dòng của DiemThi cũ)
     *      thông báo thay đổi thành công, và in ra màn hình danh sách hiện tại
     *      (Thông báo những thông tin đã được thay đổi)
     *          Nếu không thành công (do sự cố nào đó) => báo lỗi ra màn hình
     * ------------------------------------------------------------------------------------------------------------------
    **/ 
    int Update_DT(long MSSV, char maHP[], DT new_dthi){
        DT exchangeDT = {0,"",-1};           /// a blank 
        float new_diem;
        int status=-1;
        int position = CheckExist_DT_toPosition(MSSV,maHP);
        int positionOfNew = CheckExist_DT_toPosition(new_dthi.MSSV,new_dthi.maHP);
        if(position>-1 && positionOfNew >-2){               /// nếu điểm thi cũ tồn tại và bản ghi điểm chưa tồn tại nhưng hợp lệ
            exchangeDT = FindDT(position);
            if((positionOfNew==position) || (positionOfNew==-1)){
                if(exchangeDT.MSSV!=new_dthi.MSSV){
                    printf("UPDATING.....MSSV => %ld\n",new_dthi.MSSV);
                    exchangeDT.MSSV=new_dthi.MSSV;
                }
                if(strcmp(exchangeDT.maHP,new_dthi.maHP)!=0){
                    printf("UPDATING.....HocPhan => %s\n",new_dthi.maHP);
                    strcpy(exchangeDT.maHP,new_dthi.maHP);
                }
                if(IsValid_diemHP(new_dthi.diem)==0){
                    new_diem = Round_diemHP(new_dthi.diem);
                    if(exchangeDT.diem!=new_diem){
                        printf("UPDATING.....diem => %4.1f\n",new_diem);
                        exchangeDT.diem=new_diem;
                    }
                    status = ChangeStruct_To_DT_bin(position,exchangeDT);
                    if(status!=-1){
                        printf("RESULT:\n");
                        FindDT(position);
                        printf("UPDATE RECORD SUCCESSFULLY!!\n");
                    }else{
                        printf("UNFORTUNATELY, UPDATE RECORD UNSUCCESSFULLY!!\n");
                    }
                }else{
                    printf("CAN'T UPDATE Diem!!\n");
                }
            }else{
                printf("ERROR: DATA DUPLICATED!!\n");
            }
        }else{
            printf("UPDATE FAIL!!\n");
        }
        return status;
    }
    
    /** Đồng bộ lại dữ liệu cho toàn bộ file DIEMTHI 
     * -- tránh trường hợp lưu trữ sinh viên đã xóa/ thay đổi 
    **/
    void Sync_DT_binForSV(long del_MSSV){
        FILE *dtBin;
        DT dthi;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        int position;
        int statusDel=-1;
        ///------ Sychronize -----///
        dtBin= fopen(fileDIEMTHI,"rb");
        if(dtBin!=NULL){
            while(ftell(dtBin)<sizeOfFile){
                position = ftell(dtBin);
                fread(&dthi,sizeof(DT),1,dtBin);
                if(dthi.MSSV==del_MSSV){
                    statusDel = Delete_DT(del_MSSV,dthi.maHP);
                    if(statusDel!=-1){
                        fseek(dtBin,position,SEEK_SET);
                        sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
                    }else{
                        break;
                    }
                }
            }
            if(statusDel==-1){
                printf("NOTHING WILL CHANGE IN DIEMTHI.bin!!\n");
            }
        }else{
            printf("SYCHRONIZE: CANNOT OPEN FILE HP.bin\n");
        }
        fclose(dtBin);
    }

    /** Đồng bộ lại dữ liệu cho toàn bộ file DIEMTHI 
     * -- tránh trường hợp lưu trũ môn học đã xóa/ thay đổi 
    **/
    void Sync_DT_binForHP(char del_maHP[]){
        FILE *dtBin;
        DT dthi;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        int position;
        int statusDel = -1;
        ///------ Sychronize -----///
        dtBin= fopen(fileDIEMTHI,"rb");
        if(dtBin!=NULL){
            while(ftell(dtBin)<sizeOfFile){
                position = ftell(dtBin);
                fread(&dthi,sizeof(DT),1,dtBin);
                if(strcmp(dthi.maHP,del_maHP)){
                    statusDel =  Delete_DT(dthi.MSSV,dthi.maHP);
                    if(statusDel!=-1){
                        fseek(dtBin,position,SEEK_SET);
                        sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
                    }else{
                        break;
                    }
                }
            }
            if(statusDel==-1){ 
                printf("NOTHING WILL CHANGE IN DIEMTHI.bin!!\n");
            }
        }else{
            printf("SYCHRONIZE: CANNOT OPEN FILE HP.bin\n");
        }
        fclose(dtBin);
    }

#endif

