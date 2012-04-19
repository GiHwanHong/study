
void Create()
{
	imageMerger = new ImageMerger(this);
	colorReducer = new ColorReducer(this);
	histo = new Histogramer(this);

	imageViewer = new ImageViewer;
	histogramGraph = new HistogramGraph;

	connect(colorReducer, SIGNAL(output(const MonoBuffer&)),
			histo, SLOT(input(const MonoBuffer&)));
	connect(colorReducer, SIGNAL(output(const MonoBuffer&)),
			imageViewer, SLOT(setImage(const MonoBuffer&)));
	connect(histo, SIGNAL(output(const HistogramData&)),
			histogramGraph, SLOT(updateGraph(const HistogramData&)));

}


void Inspect(void)
{
	// ��� image processor �� �θ� QObject�� ���Ͽ� �Ʒ��� ������ ����.
	//
	// this->connect(longDiffer, SIGNAL(processFailed(const QString&)),
	// 				  SLOT(reportError(const QString&)));

	// ImageProcessor::link(ImageProcessor& prevObj) �� ����
	//  - �� ��ü�� resetted() �ñ׳��� ���� ��ü�� reset() ���Կ� �����Ѵ�.(�� ��ü�� �ӽû��� ����)
	//  - �� ��ü�� processed() �ñ׳��� ���� ��ü�� process() ���Կ� �����Ѵ�.(��/����� ����)
	// �Ҽ� �ֵ��� �Ͽ��� �Ѵ�.

	// N�� �̻��� ��ü�� ���� N���� processed()�� Ȯ�εǾ�� process() �ϴ� ��ü�� ���ؼ���
	// ������ ProcessMerger ��ü�� ������ �ʿ�.(�� ����� ����ȭ)

	imageResizer = new ImageResizer(this);
	{
		imageResizer->setRatio(8);
	}

	pitchDetector = new AdaptivePitchDetector(this);
	{
		pitchDetector->connect(imageResizer, SIGNAL(output(const MonoBuffer&)),
							   SLOT(input(const MonoBuffer&)));

		pitchDetector->link(imageResizer);
	}

	intensityCorrector = new LutProcessor(this);
	{
		// intensityCorrector->setUp(lookupTable);
		intensityCorrector->connect(imageResizer, SIGNAL(output(const MonoBuffer&)),
									SLOT(setImage(const MonoBuffer&)));
		intensityCorrector->connect(pitchDetector, SIGNAL(processed()),
									SLOT(process()));

		intensityCorrector->link(pitchDetector);
	}

	imageDiffer = new ImageDiffer(this);
	{
		imageDiffer->connect(intensityCorrector, SIGNAL(output(const MonoBuffer&)),
							 SLOT(input(const MonoBuffer&)));
		imageDiffer->connect(pitchDetector, SIGNAL(onPitchCalculated(double)),
							 SLOT(setPitch(double)));
		imageDiffer->link(pitchDetector);
	}

	pitchCorrector = new LongPitchCorrector(this);
	{
		pitchCorrector->connect(intensityCorrector, SIGNAL(output(const MonoBuffer&)),
								SLOT(setImage(const MonoBuffer&)));
		pitchCorrector->link(imageDiffer);
	}

	longDiffer = new ImageLongDiffer(this);
	{
		longDiffer->connect(intensityCorrector, SIGNAL(output(const MonoBuffer&)),
							SLOT(setImage(const MonoBuffer&)));
		longDiffer->connect(pitchCorrector, SIGNAL(pitchCorrected(double)),
							SLOT(setPitch(double)));
		longDiffer->link(pitchCorrector);
	}

	binarier = new BinaryImageMaker(this);
	{
		binarier->connect(imageDiffer, SIGNAL(output(const MonoBuffer&)),
						  SLOT(setDiffImage(const MonoBuffer&)));
		binarier->connect(longDiffer, SIGNAL(output(const MonoBuffer&)),
						  SLOT(setLongDiffImage(const MonoBuffer&)));
		binarier->link(longDiffer);
	}

	labeler = new ImageLabeler(this);
	{
		labeler->connect(imageResizer, SIGNAL(output(const MonoBuffer&)),
						 SLOT(setOriginalImage(const MonoBuffer&)));
		labeler->connect(binarier, SIGNAL(output(const MonoBuffer&)),
						 SLOT(setBinaryImage(const MonoBuffer&)));
		labeler->link(binarier);
	}

	imageResizer->reset(); // ������ ��� ����� ��ü�� reset()�� ȣ��.
	imageResizer->process(); // ������ ��� ����� ��ü�� reset()�� ȣ��.
}
