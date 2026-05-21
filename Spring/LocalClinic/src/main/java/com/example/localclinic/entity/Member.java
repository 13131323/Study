package com.example.localclinic.entity;

import jakarta.persistence.*;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.NoArgsConstructor;

import java.util.ArrayList;
import java.util.List;

@Entity
@Getter
@NoArgsConstructor(access = AccessLevel.PROTECTED)
public class Member extends BaseTimeEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false, unique = true)
    private String email;

    @Column(nullable = false)
    private String password;

    @Column(nullable = false)
    private String name;

    @Column(nullable = false, unique = true)
    private String phoneNum;

    @Enumerated(EnumType.STRING)
    @Column(nullable = false)
    private VerificationStatus verificationStatus; // UNVERIFIED, PENDING, VERIFIED

    @Enumerated(EnumType.STRING)
    @Column(nullable = false)
    private Role role; // PATIENT, HOSPITAL_ADMIN, SYSTEM_ADMIN

    // 양방향 매핑
    @OneToOne(mappedBy = "member", cascade = CascadeType.ALL)
    private PatientDetail patientDetail;

    @OneToOne(mappedBy = "member", cascade = CascadeType.ALL)
    private HospitalAdminDetail hospitalAdminDetail;

    @OneToMany(mappedBy = "member", cascade = CascadeType.ALL)
    private List<Waiting> waitings = new ArrayList<>();

    @OneToMany(mappedBy = "member", cascade = CascadeType.ALL)
    private List<Review> reviews = new ArrayList<>();

    @OneToMany(mappedBy = "member", cascade = CascadeType.ALL)
    private List<Favorite> favorites = new ArrayList<>();
}