package assignment;

import java.util.HashMap;

// LL파서 관련 클래스
public class Parser {
    public Lex lex;
    public HashMap<String, Double> symbolTable;

    public Parser(Lex lex, HashMap<String, Double> symbolTable) {  // 두 객체 받아오기
        this.lex = lex;
        this.symbolTable = symbolTable;
        this.lex.lexer(); 		// 첫 번째 토큰 확인
    }
    
    public void statements() {
        if (lex.next_token.equals(Token.EOI)) {		// 빈 줄이면 리턴
            return;
        }
        statement();
        stmts_tail();
        
        if (!lex.next_token.equals(Token.EOI)) {    // 끝이 EOI가 아니면 에러
            throw new RuntimeException("예기치 않은 토큰 발견 (" + lex.token_string + ")");
        }
    }

    public void stmts_tail() {
        if (lex.next_token.equals(Token.SEMI_COLON)) {
            lex.lexer();			// 세미콜론 소모
            if (!lex.next_token.equals(Token.EOI)) {
                 statement();
                 stmts_tail();
            }
        }
    }

    public void statement() {
        if (lex.next_token.equals(Token.ID)) {   // 토큰이 ID이면
            String ident = lex.token_string;    // 문자열 저장
            lex.lexer(); 			// ID 토큰 소모하고 다음으로
            if (lex.next_token.equals(Token.ASSIGN_OP)) {   // assign_op이면 소모
                lex.lexer(); 
                try {
                    double result = expression();   // 계산값 반환
                    
                    if (Double.isNaN(result)) {		// 계산결과 NaN이면 null로 저장
                        symbolTable.put(ident, null);
                    } else {
                        symbolTable.put(ident, result);  // 정상이면 값 저장
                    }
                }
                catch (RuntimeException e) { 		// 에러가 발생하면
                    symbolTable.put(ident, null);   // 계산도 실패하고 메세지 출력
                    throw e; 
                }
            }
            else {			// assign_op 아니면 에러
                throw new RuntimeException("':='가 필요. (" + lex.token_string + ")");
            }
        }
        else { 				// ident로 시작 안해도 에러
            throw new RuntimeException("식별자(ID)로 시작 해야함. (" + lex.token_string + ")");
        }
    }

    // term {(+|-) term}을 한번에 파싱
    public double expression() {
        double termResult = term();		// term 값 받기

        while (lex.next_token.equals(Token.ADD_OP)) {  // 토큰이 add_op이면 루프
            String operation = lex.token_string; 	// 무슨 연산자인지 받고
            lex.lexer();		// 연산자 토큰 소모

            double nextTermResult = term();		// 다음 term 값 받기

            if (operation.equals("+")) {		// 실제 계산
            	termResult += nextTermResult;
            }
            else {
            	termResult -= nextTermResult;
            }
        }

        return termResult;  // 계산값 반환
    }

    // factor {(*|/) factor}를 한번에 파싱 (주석 수정)
    public double term() {
        double factorResult = factor();		// factor값 받기

        while (lex.next_token.equals(Token.MUL_OP)) {	// 토큰이 mul_op이면 루프
            String operation = lex.token_string; // 무슨 연산자인지 받고
            lex.lexer();  // 연산자 토큰 소모

            double nextFactorResult = factor();		// 다음 factor 값 받기

            if (operation.equals("*")) {				// 실제 계산
            	factorResult = factorResult * nextFactorResult;
            }
            else {
            	if (nextFactorResult == 0.0) {		// 만약 0으로 나눠지면 에러
            	    throw new RuntimeException("0으로 나눌 수 없음.");
            	}
            	else factorResult = factorResult / nextFactorResult;
            }
        }
        
        return factorResult;		// 계산값 반환
    }

    public double factor() {
        // factor는 피연산자(값)가 와야 하는 자리인데, 또 연산자가 오면 문법 오류임
        if (lex.next_token.equals(Token.ADD_OP) || lex.next_token.equals(Token.MUL_OP)) {
            throw new RuntimeException("중복 연산자(" + lex.token_string + ") 발생");
        }
        
        if (lex.next_token.equals(Token.LEFT_PAREN)) {   // '('이면 소모
            lex.lexer();
            double result = expression();		// 결과 받아서 저장
            if (lex.next_token.equals(Token.RIGHT_PAREN)) {   // ')'이면 소모
                lex.lexer();
                return result;		// 결과 반환
            }
            else {  				// ')'가 아니면 에러
                throw new RuntimeException("')'가 필요. (" + lex.token_string + ")");
            }
        }
	        else if (lex.next_token.equals(Token.ID)) { 	// ident 토큰이면
	            String ident = lex.token_string;
	            
	            symbolTable.putIfAbsent(ident, null);		// 일단 심볼 테이블 삽입
	            
	            // 만약 ident null이면 NaN 반환
	            if (symbolTable.get(ident) == null) {
	            	lex.lexer();
	                return Double.NaN;
	            }
	            double value = symbolTable.get(ident); 
	            lex.lexer();
	            return value;  		// 값 반환
	        }
        else if (lex.next_token.equals(Token.CONST)) {		// const 토큰이면
            double val = Double.parseDouble(lex.token_string);   // double로 변환해서 반환
            lex.lexer();
            return val;
        }
        else { 			// 세 규칙 다 만족 못하면 에러
            throw new RuntimeException("식별자(ID), 상수(CONST), 또는 '('가 나와야 함. (" + lex.token_string + ")");
        }
    }
}