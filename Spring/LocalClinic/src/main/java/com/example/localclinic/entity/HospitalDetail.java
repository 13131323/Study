package com.example.localclinic.entity;

import jakarta.persistence.*;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Entity
@Getter
@NoArgsConstructor(access = AccessLevel.PROTECTED)
public class HospitalDetail extends BaseTimeEntity {

    @Id
    private Long id;

    @MapsId // HospitalDetail의 PK를 Hospital의 PK와 매핑
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "hospital_id")  // 외래키임을 확인
    private Hospital hospital;

    @Column(nullable = false)
    private Boolean isWheelchairAccessible;

    @Column(columnDefinition = "TEXT")
    private String doctorInfo;

    @Column(columnDefinition = "TEXT")
    private String operatingHours;

    @Column(nullable = false)
    private Integer avgWaitingTime; // 평균 대기 시간 (분 단위)
}