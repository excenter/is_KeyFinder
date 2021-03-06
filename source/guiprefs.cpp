/*************************************************************************

  Copyright 2011-2013 Ibrahim Sha'ath

  This file is part of KeyFinder.

  KeyFinder is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  KeyFinder is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with KeyFinder.  If not, see <http://www.gnu.org/licenses/>.

*************************************************************************/

#include "guiprefs.h"
#include "ui_prefsdialog.h"

PrefsDialog::PrefsDialog(QWidget *parent): QDialog(parent),ui(new Ui::PrefsDialog) {
  // map dropdown values to indices
  listMetadataWrite << METADATA_WRITE_NONE;
  listMetadataWrite << METADATA_WRITE_PREPEND;
  listMetadataWrite << METADATA_WRITE_APPEND;
  listMetadataWrite << METADATA_WRITE_OVERWRITE; // out of range for some fields
  listMetadataWriteKey << METADATA_WRITE_NONE;
  listMetadataWriteKey << METADATA_WRITE_OVERWRITE;
  listMetadataFormat << METADATA_FORMAT_KEYS;
  listMetadataFormat << METADATA_FORMAT_CUSTOM;
  listMetadataFormat << METADATA_FORMAT_BOTH;
  listStartingFreq << 27.5;
  listStartingFreq << 55;
  listStartingFreq << 110;
  listStartingFreq << 220;
  listStartingFreq << 440;
  listStartingFreq << 880;
  listHopsPerFrame << 1;
  listHopsPerFrame << 2;
  listHopsPerFrame << 4;
  listHopsPerFrame << 8;
  listTemporalWindow << KeyFinder::WINDOW_BLACKMAN;
  listTemporalWindow << KeyFinder::WINDOW_HAMMING;
  listTemporalWindow << KeyFinder::WINDOW_HANN;
  listFftFrameSize << 512;
  listFftFrameSize << 1024;
  listFftFrameSize << 2048;
  listFftFrameSize << 4096;
  listFftFrameSize << 8192;
  listFftFrameSize << 16384;
  listFftFrameSize << 32768;
  listFftFrameSize << 65536;
  listFftFrameSize << 131072;
  listFftFrameSize << 262144;
  listTuningMethod << KeyFinder::TUNING_HARTE;
  listTuningMethod << KeyFinder::TUNING_BAND_ADAPTIVE;
  listSegmentation << KeyFinder::SEGMENTATION_NONE;
  listSegmentation << KeyFinder::SEGMENTATION_ARBITRARY;
  listSegmentation << KeyFinder::SEGMENTATION_COSINE;
  listToneProfile << KeyFinder::TONE_PROFILE_KRUMHANSL;
  listToneProfile << KeyFinder::TONE_PROFILE_TEMPERLEY;
  listToneProfile << KeyFinder::TONE_PROFILE_GOMEZ;
  listToneProfile << KeyFinder::TONE_PROFILE_SHAATH;
  listToneProfile << KeyFinder::TONE_PROFILE_CUSTOM;
  listSimilarityMeasure << KeyFinder::SIMILARITY_COSINE;
  listSimilarityMeasure << KeyFinder::SIMILARITY_CORRELATION;

  // UI
  ui->setupUi(this);
  this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);

  // get values from preferences
  Preferences p;
  ui->writeToFilesAutomatically->setChecked(p.getWriteToFilesAutomatically());
  ui->parallelBatchJobs->setChecked(p.getParallelBatchJobs());
  ui->skipFilesWithExistingTags->setChecked(p.getSkipFilesWithExistingTags());
  ui->applyFileExtensionFilter->setChecked(p.getApplyFileExtensionFilter());
  ui->maxDuration->setValue(p.getMaxDuration());

  ui->tagFormat->setCurrentIndex(listMetadataFormat.indexOf(p.getMetadataFormat()));
  ui->metadataWriteTitle->setCurrentIndex(listMetadataWrite.indexOf(p.getMetadataWriteTitle()));
  ui->metadataWriteArtist->setCurrentIndex(listMetadataWrite.indexOf(p.getMetadataWriteArtist()));
  ui->metadataWriteAlbum->setCurrentIndex(listMetadataWrite.indexOf(p.getMetadataWriteAlbum()));
  ui->metadataWriteComment->setCurrentIndex(listMetadataWrite.indexOf(p.getMetadataWriteComment()));
  ui->metadataWriteGrouping->setCurrentIndex(listMetadataWrite.indexOf(p.getMetadataWriteGrouping()));
  ui->metadataWriteKey->setCurrentIndex(listMetadataWriteKey.indexOf(p.getMetadataWriteKey()));
  ui->metadataWriteFilename->setCurrentIndex(listMetadataWrite.indexOf(p.getMetadataWriteFilename()));
  ui->metadataDelimiter->setText(p.getMetadataDelimiter());

  ui->temporalWindow->setCurrentIndex(listTemporalWindow.indexOf(p.core.getTemporalWindow()));
  ui->segmentation->setCurrentIndex(listSegmentation.indexOf(p.core.getSegmentation()));
  ui->similarityMeasure->setCurrentIndex(listSimilarityMeasure.indexOf(p.core.getSimilarityMeasure()));
  ui->hopsPerFrame->setCurrentIndex(listHopsPerFrame.indexOf(p.core.getHopsPerFrame()));
  ui->fftFrameSize->setCurrentIndex(listFftFrameSize.indexOf(p.core.getFftFrameSize()));
  ui->octaves->setValue(p.core.getOctaves());
  ui->bps->setValue(p.core.getBandsPerSemitone());
  ui->octaveOffset->setChecked(p.core.getOffsetToC());
  ui->toneProfile->setCurrentIndex(listToneProfile.indexOf(p.core.getToneProfile()));
  ui->hcdfPeakPickingNeighbours->setValue(p.core.getSegPeakPickingNeighbours());
  ui->arbitrarySegments->setValue(p.core.getArbitrarySegments());
  ui->hcdfGaussianSize->setValue(p.core.getSegGaussianSize());
  ui->tuningMethod->setCurrentIndex(listTuningMethod.indexOf(p.core.getTuningMethod()));
  ui->hcdfGaussianSigma->setValue(p.core.getSegGaussianSigma());
  ui->stFreq->setCurrentIndex(listStartingFreq.indexOf(p.core.getStartingFrequencyA()));
  ui->directSkStretch->setValue(p.core.getDirectSkStretch());
  ui->detunedBandWeight->setValue(p.core.getDetunedBandWeight());
  ui->iTunesLibraryPath->setText(p.getITunesLibraryPath());
  ui->traktorLibraryPath->setText(p.getTraktorLibraryPath());
  ui->seratoLibraryPath->setText(p.getSeratoLibraryPath());

  std::vector<float> ctp = p.core.getCustomToneProfile();
  ui->maj0->setValue(ctp[0]);
  ui->maj1->setValue(ctp[1]);
  ui->maj2->setValue(ctp[2]);
  ui->maj3->setValue(ctp[3]);
  ui->maj4->setValue(ctp[4]);
  ui->maj5->setValue(ctp[5]);
  ui->maj6->setValue(ctp[6]);
  ui->maj7->setValue(ctp[7]);
  ui->maj8->setValue(ctp[8]);
  ui->maj9->setValue(ctp[9]);
  ui->maj10->setValue(ctp[10]);
  ui->maj11->setValue(ctp[11]);
  ui->min0->setValue(ctp[12]);
  ui->min1->setValue(ctp[13]);
  ui->min2->setValue(ctp[14]);
  ui->min3->setValue(ctp[15]);
  ui->min4->setValue(ctp[16]);
  ui->min5->setValue(ctp[17]);
  ui->min6->setValue(ctp[18]);
  ui->min7->setValue(ctp[19]);
  ui->min8->setValue(ctp[20]);
  ui->min9->setValue(ctp[21]);
  ui->min10->setValue(ctp[22]);
  ui->min11->setValue(ctp[23]);

  QStringList ckc = p.getCustomKeyCodes();
  ui->majKey0->setText(ckc[0]);   ui->minKey0->setText(ckc[1]);
  ui->majKey1->setText(ckc[2]);   ui->minKey1->setText(ckc[3]);
  ui->majKey2->setText(ckc[4]);   ui->minKey2->setText(ckc[5]);
  ui->majKey3->setText(ckc[6]);   ui->minKey3->setText(ckc[7]);
  ui->majKey4->setText(ckc[8]);   ui->minKey4->setText(ckc[9]);
  ui->majKey5->setText(ckc[10]);  ui->minKey5->setText(ckc[11]);
  ui->majKey6->setText(ckc[12]);  ui->minKey6->setText(ckc[13]);
  ui->majKey7->setText(ckc[14]);  ui->minKey7->setText(ckc[15]);
  ui->majKey8->setText(ckc[16]);  ui->minKey8->setText(ckc[17]);
  ui->majKey9->setText(ckc[18]);  ui->minKey9->setText(ckc[19]);
  ui->majKey10->setText(ckc[20]); ui->minKey10->setText(ckc[21]);
  ui->majKey11->setText(ckc[22]); ui->minKey11->setText(ckc[23]);
  ui->silence->setText(ckc[24]);

  ui->filterFileExtensions->setText(p.getFilterFileExtensions().join(","));

  // enable/disable fields as necessary
  tuningEnabled();
  binAdaptiveTuningEnabled();
  segmentationEnabled();
  customProfileEnabled();
  metadataDelimiterEnabled();
  applyFileExtensionFilterEnabled();

  //relative sizing on Mac/Linux only
#ifndef Q_OS_WIN
  QFont smallerFont;
  smallerFont.setPointSize(smallerFont.pointSize() - 2);
  for (int i=0; i<ui->gridLayoutKeyCodes->count(); i++)
    if (!ui->gridLayoutKeyCodes->itemAt(i)->isEmpty())
      if (ui->gridLayoutKeyCodes->itemAt(i)->widget()->inherits("QLabel"))
        ui->gridLayoutKeyCodes->itemAt(i)->widget()->setFont(smallerFont);
  for (int i=0; i<ui->customMajor->count(); i++)
    if (!ui->customMajor->itemAt(i)->isEmpty())
      if (ui->customMajor->itemAt(i)->widget()->inherits("QLabel"))
        ui->customMajor->itemAt(i)->widget()->setFont(smallerFont);
  for (int i=0; i<ui->customMinor->count(); i++)
    if (!ui->customMinor->itemAt(i)->isEmpty())
      if (ui->customMinor->itemAt(i)->widget()->inherits("QLabel"))
        ui->customMinor->itemAt(i)->widget()->setFont(smallerFont);
#endif

  //: The warning text on the Advanced Preferences tab; includes the app name at %1
  ui->lbl_warning->setText(tr("Changing these preferences may severely affect %1's accuracy. This is recommended for expert users only.").arg(GuiStrings::getInstance()->appName()));

  // validation of file extension filtering
  QRegExp regex("^([a-z0-9]+,?)*$");
  QValidator *validator = new QRegExpValidator(regex, this);
  ui->filterFileExtensions->setValidator(validator);
}

PrefsDialog::~PrefsDialog() {
  delete ui;
}

void PrefsDialog::on_savePrefsButton_clicked() {
  Preferences p;
  p.setWriteToFilesAutomatically(ui->writeToFilesAutomatically->isChecked());
  p.setParallelBatchJobs(ui->parallelBatchJobs->isChecked());
  p.setApplyFileExtensionFilter(ui->applyFileExtensionFilter->isChecked());
  p.setMetadataFormat(listMetadataFormat[ui->tagFormat->currentIndex()]);
  p.setMetadataWriteTitle(listMetadataWrite[ui->metadataWriteTitle->currentIndex()]);
  p.setMetadataWriteArtist(listMetadataWrite[ui->metadataWriteArtist->currentIndex()]);
  p.setMetadataWriteAlbum(listMetadataWrite[ui->metadataWriteAlbum->currentIndex()]);
  p.setMetadataWriteComment(listMetadataWrite[ui->metadataWriteComment->currentIndex()]);
  p.setMetadataWriteGrouping(listMetadataWrite[ui->metadataWriteGrouping->currentIndex()]);
  p.setMetadataWriteKey(listMetadataWriteKey[ui->metadataWriteKey->currentIndex()]);
  p.setMetadataWriteFilename(listMetadataWrite[ui->metadataWriteFilename->currentIndex()]);
  p.setMetadataDelimiter(ui->metadataDelimiter->text());
  p.setSkipFilesWithExistingTags(ui->skipFilesWithExistingTags->isChecked());
  p.setMaxDuration(ui->maxDuration->value());
  p.core.setTemporalWindow(listTemporalWindow[ui->temporalWindow->currentIndex()]);
  p.core.setSegmentation(listSegmentation[ui->segmentation->currentIndex()]);
  p.core.setSimilarityMeasure(listSimilarityMeasure[ui->similarityMeasure->currentIndex()]);
  p.core.setHopsPerFrame(listHopsPerFrame[ui->hopsPerFrame->currentIndex()]);
  p.core.setFftFrameSize(listFftFrameSize[ui->fftFrameSize->currentIndex()]);
  p.core.setOctaves(ui->octaves->value());
  p.core.setBandsPerSemitone(ui->bps->value());
  p.core.setOffsetToC(ui->octaveOffset->isChecked());
  p.core.setToneProfile(listToneProfile[ui->toneProfile->currentIndex()]);
  p.core.setSegPeakPickingNeighbours(ui->hcdfPeakPickingNeighbours->value());
  p.core.setArbitrarySegments(ui->arbitrarySegments->value());
  p.core.setSegGaussianSize(ui->hcdfGaussianSize->value());
  p.core.setTuningMethod(listTuningMethod[ui->tuningMethod->currentIndex()]);
  p.core.setSegGaussianSigma(ui->hcdfGaussianSigma->value());
  p.core.setStartingFrequencyA(listStartingFreq[ui->stFreq->currentIndex()]);
  p.core.setDirectSkStretch(ui->directSkStretch->value());
  p.core.setDetunedBandWeight(ui->detunedBandWeight->value());
  p.setITunesLibraryPath(ui->iTunesLibraryPath->text());
  p.setTraktorLibraryPath(ui->traktorLibraryPath->text());
  p.setSeratoLibraryPath(ui->seratoLibraryPath->text());

  std::vector<float> ctp;
  ctp.push_back(ui->maj0->value());
  ctp.push_back(ui->maj1->value());
  ctp.push_back(ui->maj2->value());
  ctp.push_back(ui->maj3->value());
  ctp.push_back(ui->maj4->value());
  ctp.push_back(ui->maj5->value());
  ctp.push_back(ui->maj6->value());
  ctp.push_back(ui->maj7->value());
  ctp.push_back(ui->maj8->value());
  ctp.push_back(ui->maj9->value());
  ctp.push_back(ui->maj10->value());
  ctp.push_back(ui->maj11->value());
  ctp.push_back(ui->min0->value());
  ctp.push_back(ui->min1->value());
  ctp.push_back(ui->min2->value());
  ctp.push_back(ui->min3->value());
  ctp.push_back(ui->min4->value());
  ctp.push_back(ui->min5->value());
  ctp.push_back(ui->min6->value());
  ctp.push_back(ui->min7->value());
  ctp.push_back(ui->min8->value());
  ctp.push_back(ui->min9->value());
  ctp.push_back(ui->min10->value());
  ctp.push_back(ui->min11->value());
  p.core.setCustomToneProfile(ctp);

  QStringList ckc;
  ckc << ui->majKey0->text() << ui->minKey0->text();
  ckc << ui->majKey1->text() << ui->minKey1->text();
  ckc << ui->majKey2->text() << ui->minKey2->text();
  ckc << ui->majKey3->text() << ui->minKey3->text();
  ckc << ui->majKey4->text() << ui->minKey4->text();
  ckc << ui->majKey5->text() << ui->minKey5->text();
  ckc << ui->majKey6->text() << ui->minKey6->text();
  ckc << ui->majKey7->text() << ui->minKey7->text();
  ckc << ui->majKey8->text() << ui->minKey8->text();
  ckc << ui->majKey9->text() << ui->minKey9->text();
  ckc << ui->majKey10->text() << ui->minKey10->text();
  ckc << ui->majKey11->text() << ui->minKey11->text();
  ckc << ui->silence->text();
  p.setCustomKeyCodes(ckc);

  p.setFilterFileExtensions(ui->filterFileExtensions->text().split(","));

  // save to QSettings and close window
  p.save();
  this->close();
}

void PrefsDialog::on_cancelButton_clicked() {
  this->close();
}

void PrefsDialog::on_advancedDefaultsButton_clicked() {
  Preferences p;
  // Musical range
  ui->stFreq->setCurrentIndex(listStartingFreq.indexOf(p.core.getStartingFrequencyADefault()));
  ui->octaves->setValue(p.core.getOctavesDefault());
  ui->octaveOffset->setChecked(p.core.getOffsetToCDefault());
  ui->bps->setValue(p.core.getBandsPerSemitoneDefault());
  // Spectral analysis
  ui->fftFrameSize->setCurrentIndex(listFftFrameSize.indexOf(p.core.getFftFrameSizeDefault()));
  ui->hopsPerFrame->setCurrentIndex(listHopsPerFrame.indexOf(p.core.getHopsPerFrameDefault()));
  ui->temporalWindow->setCurrentIndex(listTemporalWindow.indexOf(p.core.getTemporalWindowDefault()));
  ui->directSkStretch->setValue(p.core.getDirectSkStretchDefault());
  // Tuning
  ui->tuningMethod->setCurrentIndex(listTuningMethod.indexOf(p.core.getTuningMethodDefault()));
  ui->detunedBandWeight->setValue(p.core.getDetunedBandWeightDefault());
  // Segmentation
  ui->segmentation->setCurrentIndex(listSegmentation.indexOf(p.core.getSegmentationDefault()));
  ui->hcdfGaussianSize->setValue(p.core.getSegGaussianSizeDefault());
  ui->hcdfGaussianSigma->setValue(p.core.getSegGaussianSigmaDefault());
  ui->hcdfPeakPickingNeighbours->setValue(p.core.getSegPeakPickingNeighboursDefault());
  ui->arbitrarySegments->setValue(p.core.getArbitrarySegmentsDefault());
  // Classification
  ui->toneProfile->setCurrentIndex(listToneProfile.indexOf(p.core.getToneProfileDefault()));
  ui->similarityMeasure->setCurrentIndex(listSimilarityMeasure.indexOf(p.core.getSimilarityMeasureDefault()));
}

void PrefsDialog::tuningEnabled() {
  ui->tuningMethod->setEnabled(ui->bps->value() > 1);
  binAdaptiveTuningEnabled();
}

void PrefsDialog::binAdaptiveTuningEnabled() {
  ui->detunedBandWeight->setEnabled(
    ui->tuningMethod->isEnabled() &&
    listTuningMethod[ui->tuningMethod->currentIndex()] == KeyFinder::TUNING_BAND_ADAPTIVE
  );
}

void PrefsDialog::segmentationEnabled() {
  KeyFinder::segmentation_t chk = listSegmentation[ui->segmentation->currentIndex()];
  bool e = (chk == KeyFinder::SEGMENTATION_COSINE);
  ui->hcdfGaussianSigma->setEnabled(e);
  ui->hcdfGaussianSize->setEnabled(e);
  ui->hcdfPeakPickingNeighbours->setEnabled(e);
  e = (chk == KeyFinder::SEGMENTATION_ARBITRARY);
  ui->arbitrarySegments->setEnabled(e);
}

void PrefsDialog::customProfileEnabled() {
  bool e = (listToneProfile[ui->toneProfile->currentIndex()] == KeyFinder::TONE_PROFILE_CUSTOM);
  ui->maj0->setEnabled(e);
  ui->maj1->setEnabled(e);
  ui->maj2->setEnabled(e);
  ui->maj3->setEnabled(e);
  ui->maj4->setEnabled(e);
  ui->maj5->setEnabled(e);
  ui->maj6->setEnabled(e);
  ui->maj7->setEnabled(e);
  ui->maj8->setEnabled(e);
  ui->maj9->setEnabled(e);
  ui->maj10->setEnabled(e);
  ui->maj11->setEnabled(e);
  ui->min0->setEnabled(e);
  ui->min1->setEnabled(e);
  ui->min2->setEnabled(e);
  ui->min3->setEnabled(e);
  ui->min4->setEnabled(e);
  ui->min5->setEnabled(e);
  ui->min6->setEnabled(e);
  ui->min7->setEnabled(e);
  ui->min8->setEnabled(e);
  ui->min9->setEnabled(e);
  ui->min10->setEnabled(e);
  ui->min11->setEnabled(e);
}

void PrefsDialog::metadataDelimiterEnabled() {
  QList<int> indices;
  indices << ui->metadataWriteTitle->currentIndex();
  indices << ui->metadataWriteArtist->currentIndex();
  indices << ui->metadataWriteAlbum->currentIndex();
  indices << ui->metadataWriteComment->currentIndex();
  indices << ui->metadataWriteGrouping->currentIndex();
  indices << ui->metadataWriteFilename->currentIndex();
  for (int i = 0; i < indices.size(); i++) {
    metadata_write_t chk = listMetadataWrite[indices[i]];
    if (chk == METADATA_WRITE_PREPEND || chk == METADATA_WRITE_APPEND) {
      ui->metadataDelimiter->setEnabled(true);
      return;
    }
  }
  ui->metadataDelimiter->setEnabled(false);
}

void PrefsDialog::applyFileExtensionFilterEnabled() {
  ui->filterFileExtensions->setEnabled(ui->applyFileExtensionFilter->isChecked());
}

void PrefsDialog::on_bps_valueChanged(int /*bps*/) {
  tuningEnabled();
}

void PrefsDialog::on_tuningMethod_currentIndexChanged(int /*index*/) {
  binAdaptiveTuningEnabled();
}

void PrefsDialog::on_segmentation_currentIndexChanged(int /*index*/) {
  segmentationEnabled();
}

void PrefsDialog::on_toneProfile_currentIndexChanged(int /*index*/) {
  customProfileEnabled();
}

void PrefsDialog::on_metadataWriteTitle_currentIndexChanged(int /*index*/) {
  metadataDelimiterEnabled();
}

void PrefsDialog::on_metadataWriteArtist_currentIndexChanged(int /*index*/) {
  metadataDelimiterEnabled();
}

void PrefsDialog::on_metadataWriteAlbum_currentIndexChanged(int /*index*/) {
  metadataDelimiterEnabled();
}

void PrefsDialog::on_metadataWriteComment_currentIndexChanged(int /*index*/) {
  metadataDelimiterEnabled();
}

void PrefsDialog::on_metadataWriteGrouping_currentIndexChanged(int /*index*/) {
  metadataDelimiterEnabled();
}

void PrefsDialog::on_metadataWriteKey_currentIndexChanged(int /*index*/) {
  metadataDelimiterEnabled();
}

void PrefsDialog::on_metadataWriteFilename_currentIndexChanged(int /*index*/) {
  metadataDelimiterEnabled();
}

void PrefsDialog::on_applyFileExtensionFilter_stateChanged(int /*state*/) {
  applyFileExtensionFilterEnabled();
}


void PrefsDialog::on_findITunesLibraryButton_clicked() {
  QString initDir;
#ifdef Q_OS_WIN
  initDir = QDir::homePath() + "/My Music";
#else
  initDir = QDir::homePath() + "/Music/iTunes";
#endif
  //: File browse dialog launched from the Preferences window
  QString iTunesLibraryPath = QFileDialog::getOpenFileName(
    this,
    //: Title of file browse dialog launched from the Preferences window
    tr("Choose iTunes Library XML"),
    initDir,
    //: Filetype in file browse dialog launched from the Preferences window
    tr("iTunes XML (*.xml)")
  );
  if (iTunesLibraryPath.isEmpty())
    return;
  ui->iTunesLibraryPath->setText(iTunesLibraryPath);
}

void PrefsDialog::on_findTraktorLibraryButton_clicked() {
  QString initDir;
#ifdef Q_OS_WIN
  initDir = QDir::homePath() + "/My Music";
#else
  initDir = QDir::homePath() + "/Documents/Native Instruments/Traktor 2.1.2";
#endif
  QString traktorLibraryPath = QFileDialog::getOpenFileName(
    this,
    //: Title of file browse dialog launched from the Preferences window
    tr("Choose Traktor Library NML"),
    initDir,
    //: Filetype in file browse dialog launched from the Preferences window
    tr("Traktor NML (*.nml)")
  );
  if (traktorLibraryPath.isEmpty())
    return;
  ui->traktorLibraryPath->setText(traktorLibraryPath);
}

void PrefsDialog::on_findSeratoLibraryButton_clicked() {
  QString initDir;
#ifdef Q_OS_WIN
  initDir = QDir::homePath() + "/My Music";
#else
  initDir = QDir::homePath() + "/Music/_Serato_";
#endif
  QString seratoLibraryPath = QFileDialog::getOpenFileName(
    this,
    //: Title of file browse dialog launched from the Preferences window
    tr("Choose Serato database"),
    initDir,
    //: Filetype in file browse dialog launched from the Preferences window
    tr("Serato database (*)")
  );
  if (seratoLibraryPath.isEmpty())
    return;
  ui->seratoLibraryPath->setText(seratoLibraryPath);
}
