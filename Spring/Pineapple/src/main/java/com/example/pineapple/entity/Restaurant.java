package com.example.pineapple.entity;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import org.locationtech.jts.geom.Point;

import java.util.ArrayList;
import java.util.List;

@Entity
@Getter
@Setter
@NoArgsConstructor
public class Restaurant {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false)
    private String name;    //식당 이름

    private String category;    //일식,한식,카페

    //지도 표시를 위한 좌표
    //columnDefinition에 GEOMETRY를 명시해줘야 DB에 공간 데이터 타입으로 들어감.
    //spatial index를 나중에 꼭!!!! 해줘야함
    @Column(columnDefinition = "POINT SRID 4326 NOT NULL")
    private Point location;

    private String address; //도로명 주소
    
    private String phoneNumber; //식당 전화번호
    
    private String description; //식당 소개글

    private Integer totalTables;    // 전체 테이블 수

    private String thumbnailUrl; // 지도 리스트에서 보여줄 대표 이미지 (썸네일)

    private Double rating; // 별점 (0.0 ~ 5.0)

    private Integer reviewCount; // 리뷰 개수 (인기순 정렬 시 필요)

    // 영업시간 정보 (현재 영업 중인지 지도에 표시하기 위함)
    private String openTime;  // "09:00"
    private String closeTime; // "22:00"
    private String breakTime; // "15:00~17:00" (선택사항)

    // 영업 상태 (사장님이 수동으로 '오늘 휴무' 처리할 때 사용)
    @Enumerated(EnumType.STRING)
    private BusinessStatus businessStatus = BusinessStatus.OPEN;

    // 연관 관계 설정
    // CascadeType이 뭐지??
    @OneToMany(mappedBy = "restaurant", cascade = CascadeType.ALL)
    private List<DiningTable> diningTables = new ArrayList<>();

    @OneToMany(mappedBy = "restaurant", cascade = CascadeType.ALL)
    private List<Menu> menus = new ArrayList<>();
}
