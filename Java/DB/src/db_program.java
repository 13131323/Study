import java.sql.*;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class db_program {
    // 1. DB 연결 정보 (본인 환경에 맞게 수정 필수!)
    static final String DB_URL = "jdbc:mysql://database-team2.cnw00acy66fl.ap-southeast-2.rds.amazonaws.com:3306/pen_factory?serverTimezone=UTC&allowPublicKeyRetrieval=true&useSSL=false";
    static final String USER = "jonghwa"; // 본인 ID
    static final String PASS = "12345678"; // 본인 비번

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            // DB 연결
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            System.out.println("=== 볼펜 공장 관리 시스템 데이터베이스 접속 ===");

            while (true) {
                System.out.println("\n[메뉴 선택]");
                System.out.println("1. 재고 현황 조회");
                System.out.println("2. 신규 품목 등록");
                System.out.println("3. 재고 수량 수정");
                System.out.println("4. 품목 삭제");
                System.out.println("5. BOM 조회");
                System.out.println("6. 발주 필요 품목 조회");
                System.out.println("0. 종료");
                System.out.print("입력 > ");

                int choice = scanner.nextInt();
                scanner.nextLine(); // 버퍼 비우기

                if (choice == 0) {
                    System.out.println("시스템을 종료합니다.");
                    break;
                }

                switch (choice) {
                    case 1: // [Read] Item + Warehouse + Inventory 조인 조회
                        String sql1 = "SELECT i.item_name, w.location, inv.quantity, i.unit " +
                                      "FROM Inventory inv " +
                                      "JOIN Item i ON inv.item_id = i.id " +
                                      "JOIN Warehouse w ON inv.warehouse_id = w.id";
                        pstmt = conn.prepareStatement(sql1);
                        ResultSet rs = pstmt.executeQuery();
                        
                        System.out.println("\n[공장 재고 현황]");
                        System.out.printf("%-20s | %-15s | %-10s\n", "제품명", "창고위치", "수량");
                        System.out.println("----------------------------------------------------");
                        while (rs.next()) {
                            String name = rs.getString("item_name");
                            String loc = rs.getString("location");
                            int qty = rs.getInt("quantity");
                            String unit = rs.getString("unit");
                            System.out.printf("%-20s | %-15s | %d %s\n", name, loc, qty, unit);
                        }
                        break;

                    case 2: // [Create] Item 테이블에 데이터 삽입
                        System.out.println("\n[신규 자재/제품 등록]");
                        System.out.print("ID 입력 : ");
                        String newId = scanner.nextLine();
                        System.out.print("이름 입력: ");
                        String newName = scanner.nextLine();
                        System.out.print("구분 (완제품/반제품/원자재): ");
                        String newCat = scanner.nextLine();
                        System.out.print("단위 (EA/kg): ");
                        String newUnit = scanner.nextLine();
                        System.out.print("안전재고량(숫자): ");
                        int safeStock = scanner.nextInt();

                        String sql2 = "INSERT INTO Item (id, item_name, category, unit, safe_stock) VALUES (?, ?, ?, ?, ?)";
                        pstmt = conn.prepareStatement(sql2);
                        pstmt.setString(1, newId);
                        pstmt.setString(2, newName);
                        pstmt.setString(3, newCat);
                        pstmt.setString(4, newUnit);
                        pstmt.setInt(5, safeStock);
                        
                        int rows2 = pstmt.executeUpdate();
                        if (rows2 > 0) System.out.println("등록이 완료되었습니다.");
                        break;

                    case 3: // [Update] 해당 아이템이 있는 창고만 보여주고 수정
                        System.out.println("\n[재고 수량 수정]");
                        
                        // 1. 수정할 품목 ID 입력
                        System.out.print("수정할 품목 ID: ");
                        String uId = scanner.nextLine();

                        // 2. [변경됨] 해당 아이템이 실제로 존재하는 창고만 조회하는 쿼리
                        List<String> validWarehouses = new ArrayList<>();
                        String wSql = "SELECT w.id, w.location, w.category, inv.quantity " +
                                      "FROM Inventory inv " +
                                      "JOIN Warehouse w ON inv.warehouse_id = w.id " +
                                      "WHERE inv.item_id = ? " + // 입력한 아이템 ID로 필터링
                                      "ORDER BY w.location DESC";
                        
                        PreparedStatement wStmt = conn.prepareStatement(wSql);
                        wStmt.setString(1, uId); // 사용자 입력 바인딩
                        ResultSet wRs = wStmt.executeQuery();

                        // 결과가 없으면(재고가 아예 없으면) 바로 종료
                        if (!wRs.isBeforeFirst()) {
                            System.out.println("❌ 해당 품목은 현재 어떤 창고에도 재고가 없습니다.");
                            wRs.close();
                            wStmt.close();
                            break;
                        }

                        System.out.println("\n[수정할 창고 선택]");
                        int idx = 1;
                        while (wRs.next()) {
                            String wId = wRs.getString("id");
                            String wLoc = wRs.getString("location");
                            String wCat = wRs.getString("category");
                            int curQty = wRs.getInt("quantity");
                            
                            // "1. WH-PROD (A관 1층) | 현재고: 1500" 형식으로 보여줌
                            System.out.printf("%d. %s (%s - %s) | 현재고: %d\n", idx, wId, wLoc, wCat, curQty);
                            validWarehouses.add(wId); 
                            idx++;
                        }
                        wRs.close();
                        wStmt.close();

                        // 3. 번호로 선택하기
                        System.out.print("\n창고 번호 입력: ");
                        int wChoice = scanner.nextInt();
                        scanner.nextLine(); // 버퍼 비우기

                        if (wChoice < 1 || wChoice > validWarehouses.size()) {
                            System.out.println("잘못된 번호입니다. 메뉴로 돌아갑니다.");
                            break;
                        }

                        String selectedWId = validWarehouses.get(wChoice - 1);
                        System.out.println("선택된 창고: " + selectedWId);

                        // 4. 변경할 수량 입력
                        System.out.print("변경할 수량: ");
                        int newQty = scanner.nextInt();
                        scanner.nextLine(); // 버퍼 비우기

                        try {
                            // 5. 업데이트 실행
                            String sql3 = "UPDATE Inventory SET quantity = ? WHERE item_id = ? AND warehouse_id = ?";
                            pstmt = conn.prepareStatement(sql3);
                            pstmt.setInt(1, newQty);
                            pstmt.setString(2, uId);
                            pstmt.setString(3, selectedWId);

                            int rows3 = pstmt.executeUpdate();
                            
                            if (rows3 > 0) {
                                System.out.println("✅ 재고 수정이 완료되었습니다.");
                                
                                // 트리거 메시지 확인 (checkRs 사용)
                                PreparedStatement checkStmt = conn.prepareStatement("SELECT @stock_warning");
                                ResultSet checkRs = checkStmt.executeQuery();
                                
                                if (checkRs.next()) {
                                    String warningMsg = checkRs.getString(1);
                                    if (warningMsg != null) {
                                        System.out.println("\n[시스템 알림]");
                                        System.out.println(warningMsg);
                                        System.out.println("---------------------------------");
                                    }
                                }
                                checkRs.close();
                                checkStmt.close();
                            } else {
                                System.out.println("업데이트 중 오류가 발생했습니다.");
                            }
                        } catch (SQLException e) {
                            e.printStackTrace();
                        }
                        break;

                    case 4: // [Delete] Item 삭제
                        System.out.print("삭제할 품목 ID: ");
                        String dId = scanner.nextLine();
                        
                        try {
                            String sql4 = "DELETE FROM Item WHERE id = ?";
                            pstmt = conn.prepareStatement(sql4);
                            pstmt.setString(1, dId);
                            int rows4 = pstmt.executeUpdate();
                            if (rows4 > 0) System.out.println("삭제가 완료되었습니다.");
                            else System.out.println("해당 ID를 찾을 수 없습니다.");
                        } catch (SQLException e) {
                            System.out.println("[삭제 실패] 다른 테이블(재고/BOM)에서 사용 중인 품목입니다.");
                        }
                        break;
                        
                    case 5: // [Procedure] BOM 전개 조회
                        System.out.println("\n[BOM(자재명세서) 전개]");
                        
                        // 1. BOM을 볼 수 있는 품목만 가져와서 보여주기
                        List<String> bomTargetIds = new ArrayList<>();
                        String bomSql = "SELECT id, item_name, category FROM Item WHERE category IN ('완제품', '반제품') ORDER BY category DESC, item_name";
                        
                        PreparedStatement bomStmt = conn.prepareStatement(bomSql);
                        ResultSet bomRs = bomStmt.executeQuery();

                        System.out.println("\n[조회할 품목(완제품, 반제품) 선택]");
                        int bIdx = 1;
                        while (bomRs.next()) {
                            String bId = bomRs.getString("id");
                            String bName = bomRs.getString("item_name");
                            String bCat = bomRs.getString("category");
                            
                            System.out.printf("%d. [%s] %s (%s)\n", bIdx, bCat, bName, bId);
                            bomTargetIds.add(bId);
                            bIdx++;
                        }
                        bomRs.close();
                        bomStmt.close();

                        if (bomTargetIds.isEmpty()) {
                            System.out.println("조회 가능한 품목이 없습니다.");
                            break;
                        }

                        // 2. 번호 선택
                        System.out.print("\n품목 번호 입력: ");
                        int bChoice = scanner.nextInt();
                        scanner.nextLine(); // 버퍼 비우기

                        if (bChoice < 1 || bChoice > bomTargetIds.size()) {
                            System.out.println("잘못된 번호입니다. 메뉴로 돌아갑니다.");
                            break;
                        }

                        String selectedBomId = bomTargetIds.get(bChoice - 1);
                        System.out.println("선택된 품목: " + selectedBomId + "의 BOM을 조회합니다...");

                        // 3. 프로시저 호출
                        try {
                            String callSql = "{CALL Get_BOM(?)}";
                            CallableStatement cstmt = conn.prepareCall(callSql);
                            cstmt.setString(1, selectedBomId);
                            
                            boolean hasResults = cstmt.execute();

                            if (hasResults) {
                                ResultSet rsBOM = cstmt.getResultSet();
                                System.out.println("\n[필요 자재 목록 (BOM Tree)]");
                                System.out.printf("%-15s | %-20s | %-8s | %-10s | %-5s\n", "품목ID", "품목명", "구분", "소요량", "단위");
                                System.out.println("----------------------------------------------------------------------");
                                
                                while (rsBOM.next()) {
                                    String rId = rsBOM.getString("품목ID");
                                    String rName = rsBOM.getString("품목명");
                                    String rCat = rsBOM.getString("구분");
                                    double rQty = rsBOM.getDouble("소요량");
                                    String rUnit = rsBOM.getString("단위");
                                    
                                    System.out.printf("%-15s | %-20s | %-8s | %-10.3f | %-5s\n", rId, rName, rCat, rQty, rUnit);
                                }
                                rsBOM.close();
                            }
                            cstmt.close();
                        } catch (SQLException e) {
                            System.out.println("[오류] 프로시저 실행 중 문제가 발생했습니다: " + e.getMessage());
                        }
                        break;
                        
                    case 6: // [Function] 재고 부족분 조회
                        System.out.println("\n[발주 필요 품목 리스트]");

                        String shortageSql = "SELECT " +
                                             "    id, item_name, category, safe_stock, " +
                                             "    (SELECT IFNULL(SUM(quantity), 0) FROM Inventory WHERE item_id = i.id) AS current_qty, " +
                                             "    Get_Stock_Status(id) AS status " +
                                             "FROM Item i " +
                                             "HAVING status LIKE '%부족%' " +
                                             "ORDER BY category, item_name";

                        try {
                            PreparedStatement sStmt = conn.prepareStatement(shortageSql);
                            ResultSet sRs = sStmt.executeQuery();

                            boolean hasShortage = false;

                            System.out.printf("%-15s | %-20s | %-8s | %-8s | %-8s | %-15s\n", "품목ID", "품목명", "구분", "현재고", "안전재고", "상태");
                            System.out.println("-----------------------------------------------------------------------------------------");

                            while (sRs.next()) {
                                hasShortage = true;
                                String sId = sRs.getString("id");
                                String sName = sRs.getString("item_name");
                                String sCat = sRs.getString("category");
                                int sCur = sRs.getInt("current_qty");
                                int sSafe = sRs.getInt("safe_stock");
                                String sStatus = sRs.getString("status");

                                System.out.printf("%-15s | %-20s | %-8s | %-8d | %-8d | %-15s\n", sId, sName, sCat, sCur, sSafe, sStatus);
                            }

                            if (!hasShortage) {
                                System.out.println("현재 부족한 품목이 없습니다. (모든 재고 안전함)");
                            } else {
                                System.out.println("-----------------------------------------------------------------------------------------");
                            }

                            sRs.close();
                            sStmt.close();
                        } catch (SQLException e) {
                            System.out.println("[오류] 조회 중 문제가 발생했습니다: " + e.getMessage());
                        }
                        break;
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try { if (conn != null) conn.close(); } catch (Exception e) {}
        }
    }
}