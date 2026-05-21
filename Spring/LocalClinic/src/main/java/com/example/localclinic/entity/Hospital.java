package com.example.localclinic.entity;

import jakarta.persistence.*;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.locationtech.jts.geom.Point; // JTS 라이브러리 사용

import java.util.ArrayList;
import java.util.List;

@Entity
@Getter
@NoArgsConstructor(access = AccessLevel.PROTECTED)
public class Hospital extends BaseTimeEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false, unique = true)
    private String apiId; // ykiho 저장

    @Column(nullable = false)
    private String name;

    @Column(nullable = false)
    private String category;

    @Column(nullable = false)
    private String address;

    // 공간 데이터 타입인 Point 사용
    @Column(columnDefinition = "POINT", nullable = false)
    private Point point;


    // 양방향 매핑
    @OneToOne(mappedBy = "hospital", cascade = CascadeType.ALL, fetch = FetchType.LAZY)
    private HospitalDetail hospitalDetail;

    @OneToOne(mappedBy = "hospital", cascade = CascadeType.ALL, fetch = FetchType.LAZY)
    private HospitalAdminDetail hospitalAdminDetail;

    @OneToMany(mappedBy = "hospital", cascade = CascadeType.ALL)
    private List<Waiting> waitings = new ArrayList<>();

    @OneToMany(mappedBy = "hospital", cascade = CascadeType.ALL)
    private List<Review> reviews = new ArrayList<>();

    @OneToMany(mappedBy = "hospital", cascade = CascadeType.ALL)
    private List<Favorite> favorites = new ArrayList<>();
}