package com.example.pineapple.repository;

import com.example.pineapple.entity.Member;
import org.springframework.data.jpa.repository.JpaRepository;
import java.util.Optional;

public interface MemberRepository extends JpaRepository<Member, Long> {
    // 이메일로 회원 찾기 (로그인 시 필수)
    Optional<Member> findByEmail(String email);
}