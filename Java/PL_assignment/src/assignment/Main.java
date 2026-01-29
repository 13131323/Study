package assignment;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import java.util.HashMap;

import java.util.ArrayList;
import java.util.Collections;

public class Main {
    public static void main(String[] args) throws IOException { 
        
        if (args.length != 1) {
            System.out.println("Usage: java -jar Main.jar <filename>");
            System.exit(1);
        }
        String filename = args[0];
        
        HashMap<String, Double> symbolTable = new HashMap<>();

        BufferedReader reader = new BufferedReader(new FileReader(filename));
        String line;
        
        while ((line = reader.readLine()) != null) {
            String lineStripped = line.trim();
            if (lineStripped.isEmpty()) { // 빈 줄  무시
                continue;
            }
            
            Lex lex = new Lex(lineStripped);
            Parser parser = new Parser(lex, symbolTable);	// 파서 객체 생성
            System.out.println(lineStripped);		// 파싱할 줄 출력
            
            Lex countingLex = new Lex(lineStripped);   // 숫자 세는용 lexer
            int idCount = 0, constCount = 0, opCount = 0;
            
            countingLex.lexer(); // 첫 토큰 가져오기
            while (!countingLex.next_token.equals(Token.EOI)) {		// 끝까지 파싱하며 counting
                String token = countingLex.next_token;
                if (token.equals(Token.ID)) idCount++;
                else if (token.equals(Token.CONST)) constCount++;
                else if (token.equals(Token.ADD_OP) || token.equals(Token.MUL_OP)) opCount++;
                countingLex.lexer(); // 다음 토큰 가져오기
            }
            
            System.out.printf("ID: %d; CONST: %d; OP: %d;\n", idCount, constCount, opCount);
            
            try {    
                parser.statements(); 		// 파싱 시작
                System.out.println("(OK)");		// 무사히 파싱 완료

            }
            catch (RuntimeException e) {
                System.out.println("(ERROR) " + e.getMessage());  // 에러 메시지 출력
            }
        }
        reader.close(); 		// 파일 읽기 종료
        
        // 심볼 테이블에 있는 변수 결과들 출력
        System.out.print("Result ==>");
        
        ArrayList<String> sortedKeys = new ArrayList<>(symbolTable.keySet());
        Collections.sort(sortedKeys);
        
        for (String key : sortedKeys) {
            Double value = symbolTable.get(key);
            System.out.print(" " + key + ": ");
            if (value == null) {
                System.out.print("Unknown;");
            } else {
                if (value == value.intValue()) System.out.print(value.intValue() + ";");
                else System.out.print(value + ";");
            }
        }
        System.out.println();
    }
}