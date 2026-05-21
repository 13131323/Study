package com.example.localclinic.entity;

import jakarta.persistence.*;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Entity
@Getter
@NoArgsConstructor(access = AccessLevel.PROTECTED)
public class HospitalAdminDetail extends BaseTimeEntity{
    @Id
    private Long id;

    @MapsId
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "member_id")
    private Member member;

    @Column(nullable = false)
    private String licenseNum;

    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "hospital_id", unique = true, nullable = false)
    private Hospital hospital;
}
